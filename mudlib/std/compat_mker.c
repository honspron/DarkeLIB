//   Small program to bring find_object stuff up to snuff.

#include "/adm/include/security.h"



int occ;

string path;



int is_dir(string file);

int update_dir(string dir);

string add_path(string file);

void parse_file(string file);



string add_path(string file) {

  if(!path) return file;

  return path + "/" + file;

}



int is_dir(string file) {

  if(file == "." || file == "..") return 0;

  return (file_size(path+"/"+file) == -2);

}

 

void update_tree(string dir) {

  string *tmp, *dirs;

  int i, last;



  dirs = ({ dir });

  i = 2;

  last = 0;

  path = dir;

  seteuid(UID_ROOT);

  while(last < sizeof(dirs)) {

    path = dirs[last];

    i = sizeof(dirs);

    dirs += map_array(filter_array(get_dir(path+"/*"), (: is_dir :)),

		      (: add_path :));

    last++;

  }

  seteuid(getuid());

  map_array(dirs, (: update_dir :));

  return;

}



int update_dir(string dir) {

  string *list;



  seteuid(UID_ROOT);

  if(file_size(dir) != -2) {

    write("Not a directory.");

    return 1;

  }

  write("Directory: "+dir);

  list = get_dir(dir+"/*.c");

  list += get_dir(dir+"/*.h");

  path = dir + "/";

  map_array(list, (: parse_file :));

  seteuid(getuid());

  return 1;

}



void parse_file(string file) {

  int sz;

  string file_str;



  file = path+file;

  sz = file_size(file);

  if(sz <= 0) return;

  write("File: "+file);

  file_str = read_file(file);

  sz = strlen(file_str);

  file_str = replace_string(file_str,

    "load_object",

    "load_object");

  rm(file);

  write_file(file, file_str);

  if(sz != strlen(file_str))

    write(sprintf("Replaced %d occurrences.",

      (sz-strlen(file_str))/8));

  return;

}

