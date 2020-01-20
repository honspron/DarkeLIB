//    A server for the necromancer's undead dimension
//    -Diewarzau 1/28/96
//    DarkeLIB 1.0
#include <daemons.h>

inherit "/std/locker_room";
inherit "/std/virtual/compile";

void virtual_setup(string file) {
  set_short(capitalize(file)+"'s Pocket Undead Dimension");
  set_long(
  "This is "+capitalize(file)+"'s pocket undead dimension.  "
  "Undead creatures may be stored here.");
  set("owner", file);
  set_property("light", 3);
  set_property("indoors", 1);
  set_property("storage room", 1);
  return;
}

int receive_objects() {
  object prev;

  if(!(prev=previous_object())) return ::receive_objects();
  if(prev->is_pet() && stringp(prev->query_owner()) &&
	(string)prev->query_owner() != query("owner")) {
    if(prev=find_player((string)prev->query_owner()))
      message("info", "You may not store your pets there.", prev);
    return 0;
  }
  if(!prev->is_pet() && (string)prev->query_name() != query("owner")) {
    message("info", "You may not enter this private dimension.", prev);
    return 0;
  }
  if(environment(prev) && living(environment(prev))) {
    message("info", "You may not drop anything in this room.", environment(prev));
    return 0;
  }
  return ::receive_objects();
}

void open_exit(object where, int dur) {
  if(member_array("out", query_exits()) >= 0) remove_exit("out");
  add_exit(base_name(where), "out");
  if(dur) call_out("remove_out", dur);
  return;
}

int filter_player(object item) { return item->is_player(); }

void remove_out() {
  object *inv;
  int i;

  inv = filter_array(all_inventory(this_object()), "filter_player", this_object());
  if(!inv || !sizeof(inv)) return;
  message("info", "%^BOLD%^%^GREEN%^The dimension is closing.  "+
    "You are transported back to the prime material plane.%^RESET%^",
    this_object());
  i = sizeof(inv);
  while(i--) if(inv[i]) inv[i]->move_player(query_exit("out"), 0);
  remove_exit("out");
  return;
}

