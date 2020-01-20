//    An inheritable object that must be inherited by ALL rooms which wish to save locker objects past
//    reboots.  Handles all functions concerning cloning the lockers and putting them in.
//    DarkeLIB 0.1
//    -Diewarzau 7/29/95
// (TINY) Found info from Parnell copy of 1999 applying that code to here "SAVE_D fixed parnell 1999

#include "/adm/include/std.h"
#include "/adm/include/daemons.h"
#include "/adm/include/security.h"

inherit "/std/vault";

static int load_status;

void load_lockers();

void create() {
  mapping lockers;
  string *l_keys;
  int i;
  object ob;
  
  ::create();
  set_property("storage room", 1);
  if(!load_status) delayed_call("load_lockers", 2);
  return;
}

void load_lockers() {
  if(load_status) return;
  load_status = 1;
  SAVE_ITEMS_D->load_lockers(this_object());
  load_status = 2;
  return;
}

int
 query_is_locker_room() { return 1; }

int receive_objects() {
  if(!::receive_objects()) return 0;
  if(load_status < 2) return 1;
  if(previous_object() && previous_object()->query_is_locker())
    delayed_call("update_me", 1);// Logic added thanks to parnells old code added TINY 2020
  return 1;
}

void update_me() {
  SAVE_ITEMS_D->update_lockers(this_object());
  return;
}

void init() {
  ::init();
  if(!load_status) load_lockers();
  return;
}

