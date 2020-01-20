//  The anti-core daemon

#include <security.h>

void remove_core() {
  string *dir, *dir2, path;
  int i;

  seteuid(UID_ROOT);
  dir2 = ({ "/wizards" });
  while(sizeof(dir2)) {
    dir = get_dir(dir2[0]+"/*");
    path = dir2[0] + "/";
    dir2 = exclude_array(dir2, 0);
    i = sizeof(dir);
    while(i--) {
      if(file_size(path+dir[i]) == -2) {
        dir2 += ({ path+dir[i] });
        continue;
      }
      if(dir[i] == "core") {
        rm(path+dir[i]);
        write("Removed: "+path+dir[i]);
      }
    }
  }
  seteuid(getuid());
  return;
}

