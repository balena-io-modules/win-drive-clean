if (process.platform === 'win32') {
  module.exports = require('bindings')('drive-clean').clean
} else {
  module.exports = (device, callback) => {
    if (typeof device !== 'string') {
      throw new TypeError('Device must be a string')
    }

    if (typeof callback !== 'function') {
      throw new TypeError('Callback must be a function')
    }

    process.nextTick(callback)
  }
}
