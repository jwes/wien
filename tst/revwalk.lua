--revwalk
local luagi = require( "luagi" )
local test_helper = require( "test_helper" )

describe( "revwalk #revwalk", function()
   local repo = nil
   local err = nil
   local revwalk = nil
   setup( function()
      test_helper.setup()
      repo, err = luagi.open( test_helper.path )
      if err then return end
      revwalk, err = repo:revwalk()
      revwalk:sorting( {} )
      revwalk:push_head()
   end)

   it( "should be prepared", function()
      assert.is.falsy( err )
      assert.are.equal( "userdata", type( revwalk ))
      assert.is.not_nil( revwalk.sorting )
   end)

   describe( "next #revwalk", function()
      it( "should iterate elements", function()
         local rev, err= revwalk:next()
         assert.are.equal( "dfbd38f5aa968afaac607195dc88bb2add11a799", rev )
         rev, err= revwalk:next()
         assert.are.equal( "4aa7714edd19d6c8a0ccfb9a2d8650e69ae2bd09", rev )
         rev, err= revwalk:next()
         assert.are.equal( "3a3e73745d1a2ba679362d51e0a090a3ee03aad6", rev )
         rev, err= revwalk:next()
         assert.is.falsy( rev )
       end)
   end)
   describe( "repository #revwalk", function()
      it( "should return the current repo", function()
         local r, err = revwalk:repository()
         assert.is.falsy( err )
         assert.is.not_nil( r )
         assert.is.not_nil( r.path )
         assert.are.equal( repo:path(), r:path() )
      end)
   end)
end)

describe( "sorting #revwalk", function()
   local repo = nil
   local err = nil
   local revwalk = nil
   setup( function()
      test_helper.setup()
      repo, err = luagi.open( test_helper.path )
      if err then return end
      revwalk, err = repo:revwalk()
      revwalk:sorting( { reverse = true } )
      revwalk:push_head()
   end)

   it( "should be prepared", function()
      assert.is.falsy( err )
      assert.are.equal( "userdata", type( revwalk ))
      assert.is.not_nil( revwalk.sorting )
   end)

   describe( "next #revwalk", function()
      it( "should iterate elements", function()
         local rev, err= revwalk:next()
         assert.are.equal( "3a3e73745d1a2ba679362d51e0a090a3ee03aad6", rev )
         rev, err= revwalk:next()
         assert.are.equal( "4aa7714edd19d6c8a0ccfb9a2d8650e69ae2bd09", rev )
         rev, err= revwalk:next()
         assert.are.equal( "dfbd38f5aa968afaac607195dc88bb2add11a799", rev )
         rev, err= revwalk:next()
         assert.is.falsy( rev )
       end)
   end)
end)

describe( "reset #revwalk", function()
   pending( "reset" )
end)

describe( "push #revwalk", function() pending("luagi_revwalk_push ") end)
describe( "push_glob #revwalk", function() pending("luagi_revwalk_push_glob ") end)

describe( "hide #revwalk", function()
   local repo = nil
   local err = nil
   local revwalk = nil
   setup( function()
      test_helper.setup()
      repo, err = luagi.open( test_helper.path )
      if err then return end
      revwalk, err = repo:revwalk()
      revwalk:push_head()
      revwalk:hide( "3a3e73745d1a2ba679362d51e0a090a3ee03aad6" )
   end)

   it( "should be prepared", function()
      assert.is.falsy( err )
      assert.are.equal( "userdata", type( revwalk ))
      assert.is.not_nil( revwalk.sorting )
   end)

   describe( "next #revwalk", function()
      it( "should iterate elements", function()
         local rev, err= revwalk:next()
         assert.are.equal( "dfbd38f5aa968afaac607195dc88bb2add11a799", rev )
         rev, err= revwalk:next()
         assert.are.equal( "4aa7714edd19d6c8a0ccfb9a2d8650e69ae2bd09", rev )
         rev, err= revwalk:next()
         assert.is.falsy( rev )
      end)
   end)
end)

describe( "hide_glob #revwalk", function() pending("luagi_revwalk_hide_glob ") end)
describe( "hide_head #revwalk", function() pending("luagi_revwalk_hide_head ") end)
describe( "push_ref #revwalk", function() pending("luagi_revwalk_push_ref ") end)
describe( "hide_ref #revwalk", function() pending("luagi_revwalk_hide_ref ") end)
describe( "push_range #revwalk", function() pending("luagi_revwalk_push_range ") end)
describe( "simplify_first_parent #revwalk", function() pending("luagi_revwalk_simplify_first_parent ") end)
describe( "add_hide_callback #revwalk", function() pending(" luagi_revwalk_add_hide_callback ") end)
