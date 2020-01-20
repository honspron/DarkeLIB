#include <std.h>

inherit ROOM;


void create() {
  set_short("You probably shouldn't be here");
  set_long("You probably shouldn't be here");
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
  for(i = 1; i <=20; i++) {
    ob = new("/wizards/diewarzau/obj/misc/small_vial");
    ob->move(this_object());
    ob = new("/wizards/diewarzau/obj/misc/loaf");
    ob->move(this_object());
    if(i <= 15) {
      ob = new("/wizards/diewarzau/obj/misc/herb_press");
      ob->move(this_object());
      ob = new("/wizards/diewarzau/obj/misc/waterskin");
      ob->move(this_object());
      ob = new("/d/damned/virtual/footman's-mace_2.weapon");
      ob->move(this_object());
    }
    if(i <= 5) {
      ob = new("/wizards/diewarzau/obj/misc/alabaster_figurine");
      ob->move(this_object());
    }
  }
  return;
}

