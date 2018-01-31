var assert = require( 'assert' )
var driveClean = require( '..' )

context('drive', function() {

  specify('.clean()', function( done ) {
    driveClean( '\\.\PhysicalDriveX', done )
  })

})
