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
  while(i--) if(inv[i] && !living(inv[i]) && environment(inv[i]) == this_object()) inv[i]->remove();
  return;
}

void reset() {
  object *inv, ob;
  int i;

  seteuid(getuid());
  inv = all_inventory(this_object());
  call_out("remove_all", 5, inv);
  for(i = 1; i <=10; i++) {
      ob = new("/wizards/diewarzau/obj/misc/weapon_blank");
      ob->set_material("metal/steel");
      ob = new("/wizards/diewarzau/obj/misc/armour_blank");
      ob->set_material("metal/steel");
      ob = new("/wizards/diewarzau/obj/misc/weapon_blank");
      ob->set_material("metal/iron");
      ob->move(this_object());
      ob = new("/wizards/diewarzau/obj/misc/armour_blank");
      ob->set_material("metal/iron");
      ob->move(this_object());
      if(i <= 4) {
        ob = new("/wizards/diewarzau/obj/misc/forge");
        ob->move(this_object());
        ob = new("/wizards/diewarzau/obj/misc/greater_forge");
        ob->move(this_object());
        ob = new("/d/damned/virtual/war-hammer_2.weapon");
        ob->move(this_object());
      }
      if(i <= 3) {
      	ob = new("/wizards/diewarzau/obj/misc/board");
      	ob->move(this_object());
      }
  }
  return;
}

