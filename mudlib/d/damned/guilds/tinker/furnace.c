#include <std.h>
#include <move.h>

inherit ROOM;

void init() {
    ::init();
    add_action("melt_ingot", "melt");
}

int melt_ingot(string str) {
  string ing1, ing2;
  string mat;
  object ob1, ob2, blank;
  if(str) {
  	if(sscanf(str, "%s into armour blank", ing1)) {
  		ob1 = present(ing1, this_player());
    	if(!ob1) {
    	  write("You do not have "+article(ing1)+".");
   		   return 1;
    	}
    	if(!ob1->id("ingot")) {
    		write("This furnace only melts ingots.\n");
    		return 1;
    	}
    	blank = new("/wizards/diewarzau/obj/misc/armour_blank");
    	blank->set_material(replace_string((string)ob1->query_material(),
    	      "/", "", 1));
    	ob1->remove();
    	write("You have melted the ingot into a armour blank.");
    	if((int)blank->move(this_player()) != MOVE_OK) {
     		 write("You cannot carry the new blank, and you drop it.");
      	message("info", (string)this_player()->query_cap_name() +
      	  " drops "+(string)blank->query_short(), environment(this_player()),
      	    ({ this_player() }));
      	blank->move(environment(this_player()));
    }	
    return 1;
  }
  if(sscanf(str, "%s and %s into weapon blank", ing1, ing2) == 2) {
    ob1 = present(ing1, this_player());
    if(!ob1) {
      write("You do not have "+article(ing1)+".");
      return 1;
    }
    if(!ob1->id("ingot")) {
    	write("This furnace only melts ingots.\n");
    	return 1;
    }
    ob2 = present(ing2, this_player());
    if(!ob2) {
      write("You do not have "+article(ing2)+".");
      return 1;
    }
    if(!ob2->id("ingot")) {
    	write("This furnace only melts ingots.\n");
    	return 1;
    }
    if(ob1 == ob2) {
  		write("An weapon blank requires two DIFFERENT ingots.");
  		return 1;
  	}
    if((string)ob1->query_material() !=
      (string)ob2->query_material()) {
      write("The two ingots must be of the same material.");
      return 1;
    }
    blank = new("/wizards/diewarzau/obj/misc/weapon_blank");
    blank->set_material(replace_string((string)ob1->query_material(),
          "/", "", 1));
    ob1->remove();
    ob2->remove();
    write("You have melted the ingot into an weapon blank.");
    if((int)blank->move(this_player()) != MOVE_OK) {
      write("You cannot carry the new blank, and you drop it.");
      message("info", (string)this_player()->query_cap_name() +
        " drops "+(string)blank->query_short(),
        environment(this_player()), ({ this_player() }));
      blank->move(environment(this_player()));
    }
    return 1;
  }
  write("Look at the sign for help.\n");
  return 1;
  }
  write("Look at the sign for help.\n");
  return 1;
}

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set_property("no castle", 1);
    set("short", "The FURNACE");
    set("long",
"The temperature in this room is incredible, and you realize "
"that this room must be used for melting metals. All around are "
"large vats of boiling minerals. You decided to keep your distance from these "
"and instead mind your own affairs. There is sign on one wall.");
    set_items(
	(["sign" : (: call_other, this_object(), "read_sign" :) ]) );
    set_exits( 
              (["south" : "/d/damned/guilds/tinker/tinker_shop"]) );
}

int read_sign() {
  string tmp;
  int screen;

  if(!(screen=(int)this_player()->getenv("SCREEN")))
    screen = 72;
  tmp = wrap(
  "This is the furnace.  Here, you may melt ingots into "
  "armour blanks and weapon blanks, so you may fashion arms "
  "and weapon out of the various strange and powerful metals the lucky prospector will find. "
  "You need 1 ingot for a armour blank, and 2 for an "
  "weapon blank.  There is no charge...the furnace is self serve, so "
  "be careful.", screen);
  tmp += "\n";
  tmp +=
  "To melt an ingot into a armour blank:\n"
  "  melt <ingot> into armour blank\n"
  "  ex: melt mithril ingot into armour blank\n"
  "\n"
  "To melt 2 ingots into an weapon blank:\n"
  "  melt <ingot 1> and <ingot 2> into weapon blank\n"
  "  ex: melt davistone ingot 1 and davistone ingot 2\n"
  "      into weapon blank\n"
  "NOTE: The two ingots MUST be of the same material.\n";
  this_player()->more(explode(tmp, "\n"));
  return 1;
}

