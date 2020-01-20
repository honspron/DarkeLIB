#include <security.h>
#include <std.h>
#define ROOMS 5

inherit ROOM;

mapping owners;

void save_this_room();
string *query_all_owners();
string query_owner(string room);
int query_room_num(string owner);
void new_owner(string who, string room, int time);
int get_next_room();

void save_this_room() {
  seteuid(getuid());
  save_object("/wizards/excelsior/cape/inn/inn_save");
  seteuid(getuid());
  return;
}

void new_owner(string who, string room, int time) {
  object ob;
  string r_num;
  if(!owners) owners = ([]);
  if(!sscanf(room, "/wizards/excelsior/cape/inn/room%s", r_num)) return;
	
  owners[room] = ([]);
  owners[room]["owner"] = who;
  owners[room]["time"] = time;
  ob = find_object(room);
  save_this_room();
  return;
}

int query_time_left(string owner) {
  string room_file;
  if(member_array(owner, query_all_owners()) < 0)
    return 0;
  room_file = sprintf("/wizards/excelsior/cape/inn/room%d",
		      query_room_num(owner));
  if(!owners[room_file]) return 0;
  if(!mapp(owners[room_file]) || !owners[room_file]["time"]) {
    map_delete(owners, room_file);
    return 0;
  }
  return (int)owners[room_file]["time"] - time();
}

mapping query_owners() { return owners; }

string query_owner(string room) {
  object room_obj;
  int i;

  if(!owners || !owners[room]) 
  		return 0;
  if(!mapp(owners[room]) || !owners[room]["time"] ||
     !owners[room]["owner"]) {
    map_delete(owners, room);
    save_this_room();
    return 0;
  }
  if(owners[room]["time"] >= time())
     return owners[room]["owner"];
  else {
    map_delete(owners, room);
    room_obj = load_object(room);
    call_out("move_all_inv", 4, room_obj);
    save_this_room();
    return 0;
  }
}

void move_all_inv(object room_obj) {
  object *inv;
  int i;
  if(room_obj) {
    inv = all_inventory(room_obj);
    i = sizeof(inv);
    while(i--)
      if(inv[i]->query_is_locker() && inv[i]->query_closed())
	inv[i]->toggle_closed();
    inv = deep_inventory(room_obj);
    i = sizeof(inv);
    while(i--) {
      if(base_name(inv[i]) == "/std/obj/coins") inv[i]->remove();
      else
	inv[i]->move(load_object("/wizards/excelsior/cape/inn/inn_shop_store"));
    }
  }
  return;
}

int query_room_num(string owner) {
  string *room_keys;
  int i, num;

  if(!owners) return 0;
  room_keys = keys(owners);
  i = sizeof(room_keys);
  while(i--) {
    if(!mapp(owners[room_keys[i]]) || !owners[room_keys[i]]["owner"]) {
      map_delete(owners, room_keys[i]);
      save_this_room();
      continue;
    }
    if(owners[room_keys[i]]["owner"] == owner) {
      if(sscanf(room_keys[i], "%*sroom%d", num) != 2) return 0;
      else return num;
    }
  }
  return 0;
}

int get_next_room() {
  string *room_keys;
  int max, j, num;
  query_all_owners();
  max = ROOMS;
  for(j=0;j < max; j++) {
    num = j + 1;
    if(!owners || !owners[sprintf("/wizards/excelsior/cape/inn/room%d", num)])
      return num;
  }
  return 0;
}

string *query_all_owners() {
  string *ret, *room_keys;
  int i;

  if(!owners) return ({ });
  ret = ({});
  i = sizeof(room_keys = keys(owners));
  while(i--) {
    query_owner(room_keys[i]);
    if(owners[room_keys[i]])
      ret += ({ owners[room_keys[i]]["owner"] });
  }
  return ret;
}

void create() {
  ::create();
  owners = ([]);
  restore_object("/wizards/excelsior/cape/inn/inn_save");
  set_property("indoors", 1);
  set_property("light", 2);
  set_property("no attack", 1);
  set_property("no spell", 1);
  set_property("no scry", 1);
  set("short", "The South Cape Bed and Breakfast");
  set("long",
      "This is the front desk of the South Cape Bed and Breakfast. "+
      "You can get a room here at a great price, but the "+
      "rooms are in short supply. There is a sign on the wall."
	"You see a gift shop to the west.\n");
  set_items(([ "sign" : "Try reading it." ]));
  add_exit("/wizards/excelsior/cape/rooms/town1", "south");
  add_exit("/wizards/excelsior/cape/inn/shop", "west");
  add_exit("/wizards/excelsior/cape/inn/hall", "up");
  this_object()->reset();
  return;
}

void init() {
  ::init();
    add_action("read", "read");
}

int read(string str) {
  if(str != "sign") return 0;
  write(
	"Prices for rooms:\n(Real time, not Mud time)\n"+
	"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"+
        "Daily Rate:        1300 silver\n"+
       "Weekly Rate:       410 gold\n"+
       "Monthly Rate:      1500 gold\n");
  return 1;
}

void reset() {
  object ob;
  
  ::reset();
  if(!present("clerk", this_object())) {
    seteuid(getuid());
    ob = new("/wizards/excelsior/cape/inn/inn_clerk");
    ob->move(this_object());
  }
  return;
}







