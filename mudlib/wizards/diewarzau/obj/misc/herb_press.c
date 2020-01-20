//    This is an herb press necessary to use with herb lore.

#include <std.h>

inherit OBJECT;

void create() {
  ::create();
    set_name("herb press");
    set_id( ({ "press", "herb press" }) );
    set_short("An herb press");
    set_long("This press may be used to extract the essence from herbs " +
	     "for bottling.  Use 'press <what> into <container>' where "+
	     "<what> is what you wish to press and <container> is "+
	     "what you wish to press it into.");
    set_weight(15);
    set_value(15);
    return;
}

void init() {
  ::init();
    add_action("press", "press");
    return;
}

int press(string str) {
  string what, what2;
  object ob, ob2;

  if(!str || sscanf(str, "%s into %s", what, what2) != 2) return 0;
  ob = present(what, this_player());
  ob2 = present(what2, this_player());
  if(!ob) {
    write("You don't have a "+what+".");
    return 1;
  }
  if(!ob2) {
    write("You don't have a "+what2+".");
    return 1;
  }
  if((string)ob->query_name() != "grass" || !ob->query_property("quality")) {
    write("You can't press a "+what+".");
    return 1;
  }
  if(!ob2->query_vial()) {
    write("A "+what2+" can't contain potions.");
    return 1;
  }
  if(ob2->query_property("drink func")) {
    write("That vial has a potion in it already!");
    return 1;
  }
  seteuid(geteuid(this_object()));
  ob2->fill_vial("purple potion", "herb_action", 
		 "/wizards/diewarzau/obj/misc/herb_func",
		 (int)ob->query_property("quality")*(7+random(4)));
  ob->remove();
  write("You press some herbs into a potion.");
  message("info", (string)this_player()->query_cap_name() +
	  " presses some herbs into a potion.",
	  all_inventory(environment(this_player())),
	  ({ this_player() }) );
  return 1;
}























