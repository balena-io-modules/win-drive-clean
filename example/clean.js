var driveClean = require( '..' )
var argv = process.argv.slice(2)
var drive = argv.shift()

driveClean(drive, (error) => {
  console.log(error || 'OK')
})
