//   Small program to bring funcion types to snuff.
#include <security.h>

int state;
int occ;
string path;

void parse_file(string file);
string parse_file_line(string line);
int is_dir(string file);
int update_dir(string dir);
string add_path(string file);

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
  string *lines;

  file = path+file;
  sz = file_size(file);
  if(sz <= 0) return;
  write("File: "+file);
  occ = 0;
  lines = explode(read_file(file), "\n");
  state = 0;
  lines = map_array(lines, (: parse_file_line :));
  rm(file);
  write_file(file, implode(lines, "\n")+"\n");
  if(occ) write("Replaced "+occ+" occurrences.");
  if(state) write("WARNING!  Ended file in nonzero state.");
  return;
}

string parse_file_line(string line) {
  int i, len;

  if(!line) return line;
  len = strlen(line);
  if(!len) return line;
  for(i=0;i<len;i++) {
    if(line[i] != ')' && line[i] != '(' &&
       line[i] != ':') {
      if(state == 1) state = 0;
      else if(state == 3) state = 2;
      continue;
    }
    if(line[i] == '(') {
      if(state == 3) {
	state = 2;
	continue;
      }
      else if(state == 2) continue;
      state = 1;
      continue;
    }
    else if(line[i] == ':') {
      if(!state) continue;
      if(state == 1 && ((i+1) < len) && line[i+1] != ':') {
	line = line[0..i] + " call_other,"+line[(i+1)..(len-1)];
	len += 12;
	i += 12;
	state = 2;
	occ++;
	continue;
      }
      else if(state == 1) state = 0;
      else if(state == 2) state = 3;
      else if(state == 3) state = 2;
      continue;
    }
    else if(line[i] == ')') {
      if(state == 3 || state == 1) state = 0;
      continue;
    }
  }
  return line;
}

