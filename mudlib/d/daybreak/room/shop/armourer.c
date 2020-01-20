#include "../../daybreak.h"
inherit "/std/vault";

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("joseph")) {
      new(MON+"joseph")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit(ROOMS+"dbcc5", "south");
   add_exit(ROOMS+"shops/armourer_store", "east");
   set_door("wooden door", ROOMS+"shops/armourer_store", "east", "ak shop8 store");
   set_open("wooden door", 0);
   set_locked("wooden door", 1);
   set_lock_level("wooden door", 20);
   set("short","The Armoursmith Shop");
   set("long","This is the Armoursmith Shop.  Various objects of armour adorn the "
"walls and counters.  A sturdily built, sweaty shopkeeper peers at "
"you from behind a small table.  There is a large wooden door to the "
"east.  There is a sign on the wall.");
}

