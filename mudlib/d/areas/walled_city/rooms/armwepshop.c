inherit "/std/vault";
#include "../walled_city.h"

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("Gunther") && open) {
      new(MON+"gunther")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit(ROOMS+"grounds5", "south");
   add_exit(ROOMS+"/d/damned/akkad/shops/shop7_store", "east");
   set_door("wooden door", "/d/damned/akkad/shops/shop7_store", "east",
	    "ak shop7 store");
   set_open("wooden door", 0);
   set_locked("wooden door", 1);
   open = 1;
   set_door("east door", "/d/damned/akkad/ak_markne", "west",
	    "ak shop8");
    set_open("east door", 1);
   set_locked("east door", 0);
   set_lock_level("wooden door", 20);
   set("short","The Weaponsmith Shop");
   set("long",
"This is the Weaponsmith shop.  Weapons hang about on the walls and "
"decorate various tables.  A burly blacksmith grunts at you from "
"behind a large counter.\nThere is a sign on the wall.");
   set_items( (["sign":"The say reads: 'say gunther, help' for assistance.",
              "wooden door" : "It looks very sturdy."]) );
   set_open_function("open_door", "00:00:01");
   set_close_function("close_door", "00:00:00");
}

void open_door() {
  set_locked("east door", 0);
  set_open("east door", 1);
  call_other("/d/damned/akkad/ak_markne", "set_locked",
	     "east door", 0);
  call_other("/d/damned/akkad/ak_markne", "set_open",
	     "east door", 1);
  open = 1;
  this_object()->reset();
  return;
}

void close_door() {
  object ob, *inv;
  int i;
  
  ob = present("dakkon", this_object());
  if(ob) {
    ob->move(find_object_or_load("/d/standard/void"));
    ob->remove();
  }
  inv = all_inventory(this_object());
  i = sizeof(inv);
  while(i--) {
    if(living(inv[i])) {
      message("info", "The shop is closing now.  You must leave.", inv[i]);
      inv[i]->move(find_object_or_load("/d/damned/akkad/ak_markne"));
    }
  }
  set_open("east door", 0);
  set_locked("east door", 1);
  call_other("/d/damned/akkad/ak_markne", "set_open", 
		"east door", 0);
  call_other("/d/damned/akkad/ak_markne", "set_locked", 
		"east door", 1);
   open = 0;
}
