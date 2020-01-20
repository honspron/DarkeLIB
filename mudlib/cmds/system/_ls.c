//  A new, better _ls command :)



mixed *list;



mixed *make_file_str(string full_path);

string gen_output();

int sort_me(mixed *item1, mixed *item2);



int sort_me(mixed *item1, mixed *item2) {

  return strcmp(item1[0], item2[0]);

}



mixed *make_file_str(string full_path) {

  string file, sz_str;

  int x, idx, sz;



  if((x = strsrch(full_path, "/", -1)) < 0 || strlen(full_path) < 2)

    file = full_path;

  else

    file = full_path[(x+1)..];

  if(!file_size(full_path) ||

    file_size(full_path) == -1) {

    sz_str = "-";

    idx = 0;

  }

  else if(file_size(full_path) > 0) {

    sz = file_size(full_path) / 1024;

    if(sz < 1) sz = 1;

    sz_str = sprintf("%d", sz);

    if(find_object(full_path))

      idx = 1;

    else idx = 0;

  }

  else if(file_size(full_path) == -2) {

    sz_str = "";

    idx = 2;

  }

  return ({ file, sz_str, idx });

}



string gen_output() {

  int idx, max_len, i, sz, scr, len, col;

  string out, tmp;

  string *bef = ({ "", "%^GREEN%^%^BOLD%^", "%^BLUE%^%^BOLD%^" });

  string *aft = ({ "%^RESET%^ ", "%^RESET%^%^GREEN%^*%^RESET%^",

    "%^RESET%^%^BLUE%^/%^RESET%^" });

  

  sz = sizeof(list);

  len = 0;

  tmp = (string)this_player()->getenv("SCREEN");

  if(!tmp) scr = 74;

  else scr = atoi(tmp) - 1;

  for(i=0;i < sz; i++) {

    if(strlen(list[i][0]) > len)

      len = strlen(list[i][0]);

  }

  len += 6;

  col = scr / len;

  len -= 6;

  out = "";

  for(i = 0; i < sz; i++) {

    out += sprintf("%4s %s%s%*s", list[i][1],

      bef[list[i][2]], list[i][0]+aft[list[i][2]],

      len - (strlen(list[i][0])),"");

    if(!((i+1)%col)) out += "\n";

  }

   out += "\n";

  out += "A total of "+ sz +" files\n";

  return out;

}



int cmd_ls(string str) {

  string *files, path, out;

  int i, dots;



  path = 0;

  seteuid(getuid(previous_object()));

  if(str == "-a" || (str && sscanf(str, "-a %s", path)))

    dots = 1;

  else path = str;

  if(!path || path == "") path = "*";

  else if(path == "/") path += "*";

  else if(strsrch(path, "/", -1) == (strlen(path)-1))

    path = arrange_string(path, strlen(path)-1);

  if(file_size(resolv_path((string)this_player()->get_path(),

    path)) == -2)

    path += "/*";

  files = (string *)this_player()->wild_card(path);

  if(dots && path[0] != '.')

    files += (string *)this_player()->wild_card("."+path);

  if(!files || !sizeof(files)) {

    write("No such file or directory.");

    seteuid(getuid());

    return 1;

  }

  list = map_array(files, (: make_file_str :));

  list = sort_array(list, (: sort_me :));

  path = resolv_path((string)this_player()->get_path(),

    path);

  i = strsrch(path, "/", -1);

  if(i > -1) path = path[0..i];

  path += ":\n";

  this_player()->more(explode(path + gen_output(), "\n"));

  seteuid(getuid());

  return 1;

}

