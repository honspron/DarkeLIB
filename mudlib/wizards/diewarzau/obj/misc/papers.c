//	Rolling papers for the curiously strong grass of Darkemud.

#include <std.h>

inherit OBJECT;

int papers_left;

void create() {
  ::create();
  papers_left = 10;
  set_name("papers");
  set_id( ({ "paper", "papers", "rolling paper", "rolling papers" }) );
  set_short("A book of 10 rolling papers");
  set_weight(3);
  set_value(4);
  set_long("These papers can be used to roll cigarrettes and such.  "+
	"Use by typing 'roll <what> with paper' where <what> is "+
	"what you intend to smoke.");
}

void init() {
  ::init();
  add_action("roll", "roll");
}

int roll(string str) {
  string what;
  object ob, ob2;

  if(!sscanf(str, "%s with paper", what)) return 0;
  ob = present(what, this_player());
  if(!ob) {
    write("You don't see a "+what+" here!");
    return 1;
  }
  if(!ob->query_property("quality") || (string)ob->query_name() !=
    "grass") {
    write("You can't smoke "+what+"!");
    return 1;
  }
  papers_left--;
  seteuid(geteuid(this_object()));
  ob2 = new("/wizards/diewarzau/obj/misc/cig");
  ob2->set_property("quality", (int)ob->query_property("quality"));
  write("You roll the grass in a rolling paper.");
  message("info", this_player()->query_cap_name() + 
	" rolls up some grass in a rolling paper.",
	all_inventory(environment(this_player())), 
	({ this_player() }));
  ob->remove();
  ob2->move(this_player());
  if(!papers_left) remove();
  else set_short("A book of "+papers_left+" rolling papers");
  return 1;
}


