--[=[
  MIT License
  
  Copyright (c) 2016 Johannes Westhuis, Alexander Schulz
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
]=]--
local luagi = require( "luagi" )
local test_helper = require( "test_helper" )
local treeid = "064ee3e735ab74ab468be05c34e7f7fda011cb3b"
local entryid = "d1bddcecedb5ccd77aab1ee491563e4152bba1a9"

describe( "tree", function()
   local tree = nil

   setup( function()
      test_helper.extract()
      local repo = luagi.open( test_helper.path )
      tree = repo:lookup_tree( treeid )
   end)

   it( "should not be nil", function() 
      assert.is.not_nil( tree )
   end)

   describe( "entry_count #tree", function() 
      it( "should have a entry", function()
         assert.are.equal( 1, tree:entry_count() )
      end)
   end)

   describe( "id #tree", function()
      it( "should return the same id as used", function()
         assert.are.equal( treeid, tree:id() )
      end)
   end)
   describe( "entry_by* #tree", function()
      local entry_id = tree:entry_byid( entryid )
      local entry_name = tree:entry_byname( "folder" )
      local entry_index = tree:entry_byindex( 1 )
      local entry_path = tree:entry_bypath( "folder" ) 
      it( "should return an entry", function()
         assert.is.not_nil( entry_id )
         assert.are.equal( "userdata", type( entry_id ) )
      end)
      it( "should return an entry", function()
         assert.is.not_nil( entry_name )
         assert.are.equal( "userdata", type( entry_name ) )
      end)
      it( "should return an entry", function()
         assert.is.not_nil( entry_index )
         assert.are.equal( "userdata", type( entry_index ) )
      end)
      it( "should return an entry", function()
         assert.is.not_nil( entry_path )
         assert.are.equal( "userdata", type( entry_path ) )
      end)
      it( "should be the same", function()
         assert.are.equal( 0, entry_id:compare( entry_name ))
         assert.are.equal( 0, entry_id:compare( entry_index ) )
         assert.are.equal( 0, entry_id:compare( entry_path ) )
      end)
   end)

   describe( "walk #tree", function()
      count = 0
      for entry in tree:walk() do
         count = count + 1

      end

      it("should be 1", function()
         assert.are.equal( 1, count )
      end)
   end)

end) 

describe( "tree entry", function()
   local entry = nil
   local err = nil
   setup( function()
      test_helper.extract()
      local repo, err = luagi.open( test_helper.path )
      if err then return end
      local tree, err = repo:lookup_tree( treeid )
      if err then return end
      entry = tree:entry_byindex( 1 )
   end)

   it( "should not be nil", function()
      assert.is.falsy( err )
      assert.is.not_nil( entry )
   end)

   describe( "name #tree", function() 
     it( "should have the same name", function()
        assert.are.equal( "folder", entry:name() )
     end)
   end)

   describe( "filemode #tree", function() 
      it( "should have the correct filemode", function()
         assert.are.equal( "40000", entry:filemode() )
      end)
   end)
   describe( "id #tree", function()
      it( "should have a none nil id", function()
         assert.is.not_nil( entry:id() )
         assert.are.equal( entryid, entry:id() )
      end)
   end)
   describe( "type #tree", function() 
      it( "should have the tree type", function()
         assert.are.equal( "tree", entry:type() )
      end)
    end)
end)

describe( "tree_builder #tree", function()
   local builder = nil
   local filename = "new_file"
   local path = test_helper.path.."/some/"..filename
   local filehash = nil
   local err = nil

   setup( function()
      test_helper.extract()
      local repo = luagi.open( test_helper.path )
      local tree = repo:lookup_tree( treeid )
      builder, err = repo:tree_builder(tree)
      if err then return end

      local file = io.open( path, "w" )
      file:write( "some 'random' data" ) 
      file:close()

      filehash, err = luagi.hashfile( path, "blob" )
   end)
   
   it( "should not be nil", function()
      assert.is.falsy( err )
      assert.is.not_nil( builder )
   end)

   it( "should have the right hash", function() 
      assert.are.equal( "c8c47e4f0b34049547158bc26d0b0fd0f5223a60", filehash )
   end)

   describe( "insert #tree", function()
      it( "should return an oid", function()
         local erg, err = builder:insert( filename, filehash, "blob" )
         assert.is.falsy( err )
         assert.is.not_nil( erg )
      end)
   end)
end)
   
describe( "with inserted file", function()
   local builder = nil
   local filename = "new_file"
   local filename_two = "new_file_two"
   local path = test_helper.path.."/some/"
   local filehash = nil
   local filehash_two = nil
   local repo = nil
   local err = nil

   setup( function()
      test_helper.extract()
      repo, err = luagi.open( test_helper.path )
      if err then return end
      local tree, err = repo:lookup_tree( treeid )
      if err then return end
      builder, err = repo:tree_builder(tree)
      if err then return end

      local file = io.open( path..filename, "w" )
      file:write( "some 'random' data" ) 
      file:close()
      file = io.open( path..filename_two, "w" )
      file:write( "some other 'random' data" ) 
      file:close()

      filehash, err = luagi.hashfile( path..filename, "blob" )
      filehash_two, err = luagi.hashfile( path..filename_two, "blob" )
   end)

   it( "should not have an error", function()
      assert.is.falsy( err )
   end)

   local function refill()
      if builder:entry_count() == 0 then
         builder:insert( filename, filehash, "blob" )
      end
      if builder:entry_count() == 1 then
         builder:insert( filename_two, filehash_two, "blob" )
      end
   end

   describe( "clear #tree", function()
      setup( function()
               refill()
               builder:clear()
            end)
      it( "should have no entries", function()
         assert.are.equal( 0, builder:entry_count() )
      end)
   end)

   describe( "get #tree", function()
      local entry = nil
      setup( function()
               refill()
               entry, err = builder:get( filename )
            end)
      it( "no error", function()
         assert.is.falsy( err )
      end)
   end)

   describe( "get #tree", function()
      local entry = nil
      setup( function()
               refill()
               entry, err = builder:get( "nothing" )
            end)
      it( "no error", function()
         assert.is.falsy( entry )
      end)
   end)

   describe( "remove #tree", function()
      setup( function()
               refill()
               builder:remove( filename_two )
            end)
      it( "should have just one entry", function()
         assert.are.equal( 1, builder:entry_count() )
      end)
   end)

   describe( "write #tree", function()
      local oid = nil
      local result = nil
      local err = nil
      setup( function()
               refill()

               oid = builder:write( repo )
               result, err= repo:lookup_tree( oid )
            end)

      it( "should be falsy", function()
         assert.is.falsy( err )
         assert.is.not_nil( oid )
         assert.is.not_nil( result )
      end)
   end)

   describe( "filter #tree", function()
      setup( function()
               refill()
               builder:filter( function( entry ) return true end)
            end )
      it( "should have no entries left", function()
         assert.are.equal( 0, builder:entry_count() )
      end)
   end)
end)
