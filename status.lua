local wien = require( "wien" );
local repo = wien.open(".");
local function print_flags ( flags )
   if flags 
   then
      for flag, bool in pairs( flags ) do
          if bool then
            print( "\t", flag )
         end
      end
   end
end
local function print_table ( table, prefix ) 
   if table then
      for k, v in pairs( table ) do
         print( prefix, k, v )
         if type(v) == "table" then
            print_table( v, prefix.."\t" )
         end
      end
   end
end

print( " foreach" )
for path, flags in repo:status_for_each() do
   -- ignore ignored files --
   if not  flags[ "ignored" ]
   then
      print( path )
      print_flags( flags )
   end
end

print( "foreach ext only showing index in folder src" )
local options = {}
options["show"] = 1
options[1] = "src"
for path, flags in repo:status_for_each_ext( options ) do
   -- ignore ignored files --
   if not  flags[ "ignored" ]
   then
      print( path )
      print_flags( flags )
   end
end
print "file status.lua: "
local flags = repo:status_file("status.lua")
print_flags( flags )

print( "should bla.swp be ignored?", repo:status_ignored("bla.swp") )

list, err = repo:status_list() 
if not list 
then
   print( err )
end
print( "status of ", #list, " elements" )
for i = 1, #list 
do
   local t = list[i]
   local flags = t["status"]
   local head_to_index = t["head_to_index"]
   local index_to_workdir = t["index_to_workdir"]

   print_flags( flags )

   if head_to_index then
      print( "\thead to index" )
      print_table ( head_to_index, "\t\t" )
   end
   if index_to_workdir then
      print( "\tindex to workdir" )
      print_table ( index_to_workdir, "\t\t" )
   end
end
