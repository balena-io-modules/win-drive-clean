/*
 * Copyright 2017 resin.io
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <nan.h>
#include <windows.h>
#include <winioctl.h>
#include <string>
#include "drive-clean.hpp"

using v8::String;
using v8::Number;
using Nan::New;

namespace DriveClean {

class AsyncWorker : public Nan::AsyncWorker {
 public:
  explicit AsyncWorker(Nan::Callback *callback, std::string device)
    : Nan::AsyncWorker(callback) {
      devicePath = device;
    }

  ~AsyncWorker() {}

  void Execute() {
    HANDLE hDevice = INVALID_HANDLE_VALUE;
    DWORD size = 0;

    hDevice = CreateFile(
      devicePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
      NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hDevice == INVALID_HANDLE_VALUE) {
      errorCode = GetLastError();
      sysCall = "CreateFile";
      SetErrorMessage("Couldn't open handle to device");
      return;
    }

    BOOL layoutRemoved = DeviceIoControl(
      hDevice, IOCTL_DISK_DELETE_DRIVE_LAYOUT,
      NULL, 0, NULL, 0, &size, NULL);

    if (!layoutRemoved) {
      errorCode = GetLastError();
      sysCall = "IOCTL_DISK_DELETE_DRIVE_LAYOUT";
      SetErrorMessage("Couldn't delete drive layout");
      return;
    }
  }

  void HandleOKCallback() {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = { Nan::Null() };
    callback->Call(1, argv);
  }

  void HandleErrorCallback() {
    Nan::HandleScope scope;

    v8::Local<v8::Value> error = Nan::ErrnoException(
      errorCode, sysCall.c_str(),
      ErrorMessage(), devicePath.c_str());

    v8::Local<v8::Value> argv[] = { error };

    callback->Call(1, argv);
  }

 private:
  std::string devicePath;
  std::string sysCall;
  DWORD errorCode;
};

}  // namespace DriveClean

NAN_METHOD(clean) {
  if (!info[0]->IsString()) {
    return Nan::ThrowTypeError("Device must be a string");
  }

  if (!info[1]->IsFunction()) {
    return Nan::ThrowTypeError("Callback must be a function");
  }

  Nan::Utf8String device(info[0]->ToString());
  Nan::Callback *callback = new Nan::Callback(info[1].As<v8::Function>());

  std::string devicePath(*device);

  Nan::AsyncQueueWorker(new DriveClean::AsyncWorker(callback, devicePath));

  info.GetReturnValue().SetUndefined();
}

NAN_MODULE_INIT(InitAll) {
  NAN_EXPORT(target, clean);
}

NODE_MODULE(DriveClean, InitAll);
