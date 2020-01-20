#include <std.h>

inherit "/std/vault";

void create() {
  ::create();
  set_short("You probably shouldn't be here!");
  set_long(
	   "This is the storage room for the fighter's shop. Lots of "
	   "valuable looking wares lie about.");
  set_property("light", 2);
  set_property("indoors", 1);
  set_property("storage room", 1);
  add_exit("/d/damned/guilds/fighter/fighter_shop", "north");
  set_door("iron door", "/d/damned/guilds/fighter/fighter_shop", "north",
	   "fighter store key");
  set_open("iron door", 0);
  set_locked("iron door", 1);
  set_lock_level("iron door", 22);
  return;
}

void reset() {
  object *inv, bob;
  int i;

  ::reset();
  seteuid(getuid());
  inv = all_inventory(this_object());
  i = sizeof(inv);
  while(i--) if(!living(inv[i])) inv[i]->remove();
  bob = present("shopkeeper", 
		find_object_or_load("/d/damned/guilds/fighter/fighter_shop"));
  if(bob) {
    message("info", "Bob says in Common: Wait a second.  I've got a new "+
	    "shipment coming in...", environment(bob));
    call_out("finish_deliver", 12, bob);
  }
  for(i = 1; i <=5; i++)
    call_out("clone_once", 2*i);
  return;
}

void finish_deliver(object bob) {
  if(bob)
    message("info", "Bob says in Common: It's all here now.",
	    environment(bob));
  return;
}

void clone_once() {
  object ob;

  ob = new("/d/damned/virtual/long-sword_3.weapon");
  ob->move(this_object());
  ob = new("/d/damned/virtual/two-handed-sword_3.weapon");
  ob->move(this_object());
  ob = new("/d/damned/virtual/footman's-flail_2.weapon");
  ob->move(this_object());
  ob = new("/d/damned/virtual/footman's-mace_4.weapon");
  ob->move(this_object());
  ob = new("/d/damned/virtual/bastard-sword_3.weapon");
  ob->move(this_object());
  ob = new("/d/damned/virtual/short-sword_3.weapon");
  ob->move(this_object());
}
