var assert = require('assert')
var driveClean = require('..')

context('drive', function () {
  context('.clean()', function (done) {
    specify('should be a NOOP on non-win32 platforms', function(done) {
      if (process.platform !== 'win32') {
        driveClean('\\\\.\\PhysicalDriveX', done)
      } else {
        this.skip()
      }
    })
  })
})
