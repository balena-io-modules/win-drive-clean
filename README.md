# win-drive-clean
[![npm](https://img.shields.io/npm/v/win-drive-clean.svg?style=flat-square)](https://npmjs.com/package/win-drive-clean)
[![npm license](https://img.shields.io/npm/l/win-drive-clean.svg?style=flat-square)](https://npmjs.com/package/win-drive-clean)
[![npm downloads](https://img.shields.io/npm/dm/win-drive-clean.svg?style=flat-square)](https://npmjs.com/package/win-drive-clean)
[![Travis CI status](https://img.shields.io/travis/resin-io-modules/win-drive-clean/master.svg?style=flat-square&label=linux)](https://travis-ci.org/resin-io-modules/win-drive-clean/branches)
[![AppVeyor status](https://img.shields.io/appveyor/ci/resin-io/win-drive-clean/master.svg?style=flat-square&label=windows)](https://ci.appveyor.com/project/resin-io/win-drive-clean/branch/master)
[![Dependency status](https://img.shields.io/david/resin-io-modules/win-drive-clean.svg?style=flat-square)](https://david-dm.org/resin-io-modules/win-drive-clean)
[![Gitter Chat](https://img.shields.io/gitter/room/resin-io/etcher.svg?style=flat-square)](https://gitter.im/resin-io/etcher)

Remove a disks partition table on Windows

## Install via [npm](https://npmjs.com)

```sh
$ npm install --save win-drive-clean
```

## Usage

```js
const driveClean = require('win-drive-clean')
```

**NOTE:** As this is Windows only, calling `driveClean()` on other platforms will be a NOOP and always succeed.

```js
driveClean('\\\\.\\PhysicalDrive5', (error) => {
  // ...
})
```
