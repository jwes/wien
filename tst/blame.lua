local luagi = require("luagi")
local test_helper = require("test_helper")

describe( "blame_file #blame", function() 
   local blame = nil

   setup( function()
      test_helper.extract()
      local repo = luagi.open( test_helper.path )
      blame, err = repo:blame_file( "some/folder/testfile2" )
   end)

   it( "should have result", function()
      assert.is.not_nil( blame )
      assert.are.equal("userdata", type( blame ))
      assert.is.falsy( err )
   end)
  
   it( "should have n hunks", function()
      assert.is.equal( 1, blame:count() )
   end)

   describe( "hunks by index", function()
      local hunk, err = blame:byindex( 1 )
      it( "should be a valid object", function()
         assert.is.not_nil( hunk )
         assert.are.equal("table", type( hunk ))
         assert.is.falsy( err )
      end)

      it( "should have the right content", function()
         assert.is.equal("3a3e73745d1a2ba679362d51e0a090a3ee03aad6",
                         hunk.final.oid )
      end)

      it( "should return error", function()
         local h, err = blame:byindex( 0 )
         assert.is.falsy(h)
         assert.are.equal("string", type(err) )
      end)
      it( "should return error", function()
         local h, err = blame:byindex( -10 )
         assert.is.falsy(h)
         assert.are.equal("string", type(err) )
      end)
      it( "should return error", function()
         local h, err = blame:byindex( 2 )
         assert.is.falsy(h)
         assert.are.equal("string", type(err) )
      end)
      it( "should return error", function()
         local h, err = blame:byindex( 10 )
         assert.is.falsy(h)
         assert.are.equal("string", type(err) )
      end)

   end)

   describe( "hunks by line", function()
      local hunk, err = blame:byline( 1 )
      it( "should be a valid object", function()
         assert.is.not_nil( hunk )
         assert.are.equal("table", type( hunk ))
         assert.is.falsy( err )
      end)

      it( "should have the right content", function()
         assert.is.equal("3a3e73745d1a2ba679362d51e0a090a3ee03aad6",
                         hunk.final.oid )
      end)

      it( "should return error", function()
         local h, err = blame:byline( 0 )
         assert.is.falsy(h)
         assert.are.equal("string", type(err) )
      end)
      it( "should return error", function()
         local h, err = blame:byline( -10 )
         assert.is.falsy(h)
         assert.are.equal("string", type(err) )
      end)

   end)
   
end)
   
describe( "buffer #blame", function() pending("luagi_blame_buffer ") end)
