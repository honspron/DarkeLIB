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
  while(i--) 
    if( inv[i] && 
        !living(inv[i]) &&
        environment(inv[i]) == this_object())
      inv[i]->remove();
  return;
}

void reset() {
  object *inv, ob;
  int i,x;

  seteuid(getuid());
  inv = all_inventory(this_object());
  call_out("remove_all", 5, inv);
  for(i = 1; i <=20; i++) {
    ob = new("/std/diewarzau/obj/misc/small_vial");
    ob->move(this_object());
    ob = new("/std/diewarzau/obj/misc/loaf");
    ob->move(this_object());
    switch(random(5)) {
      case 0:
        ob = new("/d/damned/guilds/cleric/waterskin");
        break;
      case 1:
        ob = new("/d/damned/guilds/cleric/flask");
        break;
      case 2:
        ob = new("/d/damned/guilds/cleric/w_bottle");
        break;
      case 3:
        ob = new("/d/damned/guilds/cleric/wineskin");
        break;
      case 4:
        ob = new("/d/damned/guilds/cleric/w_jar");
        break;
      default:
        ob = new("/std/diewarzau/obj/misc/waterskin");
    }
    ob->move(this_object());
    x=random(4)+2;
    switch(random(5)) {
      case 0:
        ob = new("/d/damned/virtual/footman's-mace_"+x+".weapon");
        break;
      case 1:
        ob = new("/d/damned/virtual/footman's-flail_"+x+".weapon");
        break;
      case 2:
        ob = new("/d/damned/virtual/morning-star_"+x+".weapon");
        break;
      case 3:
        ob = new("/d/damned/virtual/war-hammer_"+x+".weapon");
        break;
      case 4:
        ob = new("/d/damned/virtual/hammer_"+x+".weapon");
        break;
      default:
        ob = new("/d/damned/virtual/hammer_"+x+".weapon");
    }
    if(random(100) > 95) {
      ob->set_wc(ob->query_wc(), "holy");
      ob->set_property("enchantment", 5);
      ob->set_property("no decay", 1);
      ob->set_verb("pound");
      ob->set_property("no add quality", 1);
      ob->set_value(7500+random(2500));
    }
    ob->move(this_object());
    if(i <= 2) {
      ob = new("/std/diewarzau/obj/misc/herb_press");
      ob->move(this_object());
      ob = new("/std/diewarzau/obj/misc/alabaster_figurine");
      ob->move(this_object());
    }
  }
  return;
}
