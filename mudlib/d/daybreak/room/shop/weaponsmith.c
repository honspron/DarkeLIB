#include "../../daybreak.h"
inherit "/std/vault";

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("dakkon")) {
      new(MON+"dakkon")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit(ROOMS+"dbvl6", "west");
   add_exit(ROOMS+"weaponsmith_store", "east");
   set_door("wooden door", ROOMS+"weaponsmith_store", "east","ak shop7 store");
   set_open("wooden door", 0);
   set_locked("wooden door", 1);
   set_lock_level("wooden door", 20);
   set("short","The Weaponsmith Shop");
   set("long","This is the Weaponsmith shop.  Weapons hang about on the walls and "
"decorate various tables.  A burly blacksmith grunts at you from "
"behind a large counter.\nThere is a sign on the wall.");
   set_items( (["sign":"The say reads: 'say dakkon, help' for assistance.",
              "wooden door" : "It looks very sturdy."]) );
}
