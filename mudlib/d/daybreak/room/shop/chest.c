#include "../../daybreak.h"
inherit "/std/vault";

private int open;

void reset() {
   ::reset();
   seteuid(getuid());
   if (!present("gil")) {
      new(MON+"gil")->move(this_object());
   }
  if(!present("key rack")){
        new("/d/damned/akkad/obj/misc/key_rack")->move(this_object());
  }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit(ROOMS+"dbcc2", "west");
   add_exit(ROOMS+"chest_store", "north");
   set_door("wooden door", ROOMS+"chest_store", "north","ak shop6 store");
   set_open("wooden door", 0);
   set_locked("wooden door", 1);
   set_lock_level("wooden door", 35);
   set("short","The Chest Shop");
   set("long",
"This is the Chest Shop.  Here you may buy chests and the like "
"to store your items past the daily reboots.  You must store "
"the chests in special rooms that save items, such as rooms at "
"the inn.  Chests must be closed to store items.  There is a sign on the wall.\n"
"To the north is a sturdy wooden door.\n"
);
   set_items( (["sign": (: call_other, this_object(), "read_sign" :),
              "wooden door" : "It looks very sturdy.",
              "east door" : "It is a large wooden door.",
              "door" : "There is an east door and a wooden door" ]) );
}

int read_sign() {
string msg;

  msg =
"The following chests are available:\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
"Small Chest          Stores 5 items (2000 coins weight)\n"
"Large Chest          Stores 8 items (3200 coins weight)\n"
"Storage Locker       Stores 25 items (15000 coins weight)\n"
"                     Can be used to store inventory of shops\n"
"Safe                 Can store about 100,000 coins (money only)\n"
"\n'say gil, help' for assistance.\n";
  this_player()->more(explode(msg, "\n"));
  return 1;
}
