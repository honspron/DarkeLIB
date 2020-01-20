//    Mine daemon for player mines.
//    -Diewarzau 1/28/96
//    DarkeLIB 1.0

#include "/adm/include/security.h"
#include "/adm/include/dirs.h"
#include "/adm/include/rooms.h"
#define MINERALS ({ "iron", "eog","mithril", "elrodnite", \
        "platnite", "laen", "mabril", "javednite", \
	"mcgrail", "raysorite", "inniculmoid", "boernerine", \
        "iysaughton", "davistone", "catoetine" })

mapping mines;

void save_me();

void create() {
  mines = ([]);
  seteuid(UID_DAEMONSAVE);
  if(file_exists(DIR_DAEMONS_SAVE+"/mines.o"))
    restore_object(DIR_DAEMONS_SAVE+"/mines");
  seteuid(getuid());
  if(!event_pending(this_object())) {
    this_object()->stock_mines();
    event("stock_mines", 32400, 0, 1);
  }
  return;
}

void destroy_mine(string file) {
  if(!mines[file]) return;
  else mines[file] = time() - 1000;
  save_me();
  return;
}

void save_me() {
  seteuid(UID_DAEMONSAVE);
  save_object(DIR_DAEMONS_SAVE+"/mines");
  seteuid(getuid());
}

void register_mine(string file) {
  if(mines[file]) mines[file] += 2678400;
  else mines[file] = time() + 2678400;
  save_me();
  return;
}

int time_left(string file) {
  if(!mines[file]) return 0;
  return mines[file] - time();
}

void remove_mine(string file) {
  map_delete(mines, file);
  save_me();
}

void stock_mines() {
  object room, land, *inv;
  int i, east, south, j, chance, num;
  string *m_keys, who, *no_file;

  m_keys = keys(mines);
  i = sizeof(m_keys);

  no_file = ({});
  while(i--) {
    if(sscanf(m_keys[i], "/d/damned/virtual/%s_mine2_%d_%d.mine", who, east, south) != 3) continue;
    room = find_object_or_load(m_keys[i]);
    if(mines[m_keys[i]] < time()) {
      no_file += ({ m_keys[i] });
      seteuid(UID_DAMNED_DATA);
      if(file_exists("/d/damned/data/mines/"+who+"_mine.o"))
        rm("/d/damned/data/mines/"+who+"_mine.o");
      seteuid(getuid());
      continue;
    }
    land = find_object_or_load(sprintf("/d/damned/virtual/room_%d_%d.world",
            east, south));
    j = sizeof(MINERALS);
    while(j--) {
      num = 0;
      chance = (int)land->query_mineral(MINERALS[j]);
      while(chance - 100 > 0) {
        if(random(100) < 70) num++;
        chance -= 100;
      }
      if(random(100) < chance) num++;
      room->add_mineral(MINERALS[j], num);
    }
  }
  if(!sizeof(no_file)) return;
  seteuid(UID_DAMNED_DATA);
  m_keys = explode(read_file("/d/damned/data/world_items.db"), "\n");
  rm("/d/damned/data/world_items.db");
  j = sizeof(m_keys);
  while(j--) {
    num = 0;
    who = replace_string(m_keys[j], "mine1", "mine2");
    for(i=0;i<sizeof(no_file);i++) {
      if(replace_string(who, no_file[i], "") != who)
        num = 1;
    }
    if(!num)
      write_file("/d/damned/data/world_items.db", m_keys[j]+"\n");
  }
  seteuid(getuid());
  i = sizeof(no_file);
  while(i--) {
    sscanf(no_file[i],"/d/damned/virtual/%*s_mine2_%d_%d.mine", east, south);
    inv = all_inventory(room=find_object_or_load(sprintf("/d/damned/virtual/room_%d_%d.world", east, south)));
    j = sizeof(inv);
    message("info", "A mine here is quickly torn down by a small army of dwarves.",
         room);
    while(j--) if(inv[j]) inv[j]->move(ROOM_VOID);
    who = base_name(room);
    seteuid(UID_ROOT);
    destruct(room);
    seteuid(getuid());
    j = sizeof(inv);
    while(j--) if(inv[j]) inv[j]->move(who);
    this_object()->remove_mine(no_file[i]);
  }
  return;
}

