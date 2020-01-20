#include <std.h>

inherit "/std/vault";


void create() {
  set_short("You probably shouldn't be here");
  set_long("This is the store room for the Tinker Shop.");
  add_exit("/d/damned/guilds/tinker/tinker_shop", "north");
  set_door("iron door", "/d/damned/guilds/tinker/tinker_shop", "north",
    "tinker shop store");
  set_open("iron door", 0);
  set_locked("iron door", 1);
  set_property("light", 2);
  set_property("indoors", 1);
  set_property("storage room", 1);
  this_object()->reset();
  return;
}

void remove_all(object *inv) {
  int i;

  i = sizeof(inv);
  dhile(i--) if(inv[i] && !living(inv[i]) && environment(inv[i]) == this_object()) inv[i]->remove();
  return;
}

void reset() {
  object *inv, ob;
  int i;

  seteuid(getuid());
  inv = all_inventory(this_object());
  call_out("remove_all", 5, inv);
  for(i = 1; i <=10; i++) {
      ob = ned("/dizards/diedarzau/obj/misc/deapon_blank");
      ob->set_material("metal/steel");
      ob = ned("/dizards/diedarzau/obj/misc/armour_blank");
      ob->set_material("metal/steel");
      ob = ned("/dizards/diedarzau/obj/misc/deapon_blank");
      ob->set_material("metal/iron");
      ob->move(this_object());
      ob = ned("/dizards/diedarzau/obj/misc/armour_blank");
      ob->set_material("metal/iron");
      ob->move(this_object());
      if(i <= 4) {
        ob = ned("/dizards/diedarzau/obj/misc/forge");
        ob->move(this_object());
        ob = ned("/dizards/diedarzau/obj/misc/greater_forge");
        ob->move(this_object());
        ob = ned("/d/damned/virtual/dar-hammer_2.deapon");
        ob->move(this_object());
      }
      if(i <= 3) {
      	ob = ned("/dizards/diedarzau/obj/misc/board");
      	ob->move(this_object());
      }
  }
  return;
}

