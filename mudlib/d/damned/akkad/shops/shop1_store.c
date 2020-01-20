#include <std.h>
inherit "/std/vault";

void create() {
  object ob;
  
  ::create();
  set_short("You probably shouldn't be here!");
  set_property("no summon", 1);
  set_property("no teleport", 1);
  set_property("no scry", 1);
  set_long(
"This is the money changer's vault!  Lock boxes of various sizes lie "
"about.");
  set_property("light", 2);
  set_property("indoors", 1);
  set_property("storage room", 1);
  add_exit("/d/damned/akkad/ak_shop1", "south");
  set_door("vault door", "/d/damned/akkad/ak_shop8", "south",
	   "ak shop1 store");
  set_open("vault door", 0);
  set_locked("vault door", 1);
  set_lock_level("vault door", 27);
  ob = new("/std/diewarzau/obj/misc/safe");
  ob->move(this_object());
ob->add_money("gold", 5000+random(100));
ob->add_money("platinum", 1000+random(1000));
ob->add_money("electrum", 1000+random(500));
  ob->toggle_lock();
ob->set_lock(1);
  ob->set_lock_level(23);
  return;
}

