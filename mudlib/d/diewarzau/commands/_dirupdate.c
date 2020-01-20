// Work began on this file by Darkone on 2/20/93
#include <std.h>
inherit DAEMON;

int cmd_dirupdate(string str) {
  string file, tmp, *dir;
  object ob;
  int i;

  if(!str) {
    notify_fail("dirupdate <directory>\n");
    return 0;
  }
  file = resolv_path((string)this_player()->get_path(), str);
  if(file_size(file) != -2) {
    notify_fail(file + " is not a directory.\n");
    return 0;
  }
  dir = get_dir(file + "/");
  for(i = 0; i < sizeof(dir); i++) {
     while(ob = find_object(file + "/" + dir[i])) {
       write( "Updating..." + file + "/" + dir[i] + "\n");
       if(functionp((: call_other, ob, "remove" :))) ob->remove();
	else destruct(ob);
     }
   }
   write("Update done.\n");
   return 1;
}

int help()
{
  write( @EndText
Syntax: dirupdate <directory>
Effect: updates all objects in <directory>
See also: update, dir
EndText
  );
  return 1;
}
