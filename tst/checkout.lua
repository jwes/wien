   --checkout
local luagi = require( "luagi" )
local test_helper = require( "test_helper" )
local file = "testfile"
local treeid = "064ee3e735ab74ab468be05c34e7f7fda011cb3b"

local work_branch = "55c33519ff7e7ae27372a6f338e635b3c18cca57"
local file2 = "some/folder/testfile2"

describe( "checkout_head #checkout", function()
   local repo = nil

   setup(function()
      test_helper.setup()
      repo, err = luagi.open( test_helper.path )
      if err then return end
      local file = io.open( test_helper.path.."/"..file, "w" )
      file:write( "foo, bar, baz" )
   end)

   it( "should be prepared", function()
      assert.is.falsy( err )
      assert.is.not_nil( repo )

      local flags = repo:status_file( file )
      assert.is.True( flags.workdir_modified )
   end)

   describe( "checkout should revert the changes", function()
      setup(function()
         assert.has_no_error( function() repo:checkout_head({}) end) -- no options == dry-run

         local opts = {
            flags = {
               force = true,
            },
         }
         repo:checkout_head(opts) -- no options == dry-run
      end)

      it( "should be unmodified", function()
         local flags = repo:status_file( file )
         assert.is.False( flags.workdir_modified )
      end)
   end)
end)

describe( "checkout_index #checkout", function()
   local repo = nil

   setup(function()
      test_helper.setup()
      repo, err = luagi.open( test_helper.path )
      if err then return end
      local file = io.open( test_helper.path.."/"..file, "w" )
      file:write( "foo, bar, baz" )
   end)

   it( "should not have an error", function()
      assert.is.falsy( err )
   end)

   it( "should be prepared", function()
      assert.is.falsy( err )
      assert.is.not_nil( repo )

      local flags = repo:status_file( file )
      assert.is.True( flags.workdir_modified )
   end)

   describe( "checkout should revert the changes", function()
      setup(function()
         local ind, err = repo:index()
         assert.is.falsy(err)
         assert.is.not_nil(ind)

         local opts = {
            flags = {
               force = true,
            },
         }

         repo:checkout_index( ind, { flags = { force = true } })
      end)

      it( "should be unmodified", function()
         local flags = repo:status_file( file )
         assert.is.False( flags.workdir_modified )
      end)
   end)
end)

describe( "checkout_tree #checkout", function()
   local repo = nil

   setup(function()
      test_helper.setup()
      repo, err = luagi.open( test_helper.path )
   end)

   it( "should not have an error", function()
      assert.is.falsy( err )
   end)

   it( "should be prepared", function()
      local obj, err = repo:lookup_object( work_branch, "commit" )
      assert.is.falsy( err )

      repo:checkout_tree( obj, { flags = { force = true } })

      local file = io.open( test_helper.path.."/"..file2, "r" )
      local content = file:read("*all")
      local str = "changed content"
      assert.are.equal(str, string.sub(content, 0, #str) )
   end)

end)


