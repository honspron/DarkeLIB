string *file;

int clean_up() {
  return 0;
}

void create() {
  seteuid(getuid());
file = read_database("/wizards/excelsior/tinker/data/weapon_types");
  return;
}

string query_line(int l) {
  if(l >= sizeof(file)) return 0;
  return file[l];
}

