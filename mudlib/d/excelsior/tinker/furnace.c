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
  	if(sscanf(str, "%s into weapon blank", ing1)) {
  		ob1 = present(ing1, this_player());
    	if(!ob1) {
    	  write("You do not have "+article(ing1)+".");
   		   return 1;
    	}
    	if(!ob1->id("ingot")) {
    		write("This furnace only melts ingots.\n");
    		return 1;
    	}
    	blank = new("/wizards/diewarzau/obj/misc/weapon_blank");
    	blank->set_material(replace_string((string)ob1->query_material(),
    	      "/", "", 1));
    	ob1->remove();
    	write("You have melted the ingot into a weapon blank.");
    	if((int)blank->move(this_player()) != MOVE_OK) {
     		 write("You cannot carry the new blank, and you drop it.");
      	message("info", (string)this_player()->query_cap_name() +
      	  " drops "+(string)blank->query_short(), environment(this_player()),
      	    ({ this_player() }));
      	blank->move(environment(this_player()));
    }	
    return 1;
  }
  if(sscanf(str, "%s and %s into armour blank", ing1, ing2) == 2) {
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
  		write("An armour blank requires two DIFFERENT items.");
  		return 1;
  	}
    if((string)ob1->query_material() !=
      (string)ob2->query_material()) {
      write("The two ingots must be of the same material.");
      return 1;
    }
    blank = new("/wizards/diewarzau/obj/misc/armour_blank");
    blank->set_material(replace_string((string)ob1->query_material(),
          "/", "", 1));
    ob1->remove();
    ob2->remove();
    write("You have melted the ingot into an armour blank.");
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
	"This is the furnace.  The heat in here is amazing, and you fear "
	"that you may suddenly burst into flame!  When that does not seem "
	"forthcoming, you enter.  Through the heat and smoke, you see a sign on "
	"the wall.");
    set_items(
	(["sign" : (: call_other, this_object(), "read_sign" :) ]) );
    set_exits( 
              (["east" : "/d/damned/guilds/tinker/tinker_shop"]) );
}

int read_sign() {
  string tmp;
  int screen;

  if(!(screen=(int)this_player()->getenv("SCREEN")))
    screen = 72;
  tmp = wrap(
  "This is the furnace.  Here, you may melt ingots into "
  "weapon blanks and armour blanks, so you may fashion arms "
  "and armour out of the various exotic metals to be found around "
  "DarkeMUD.  You need 1 ingot for a weapon blank, and 2 for an "
  "armour blank.  There is no charge...the furnace is self serve, so "
  "be careful.", screen);
  tmp += "\n";
  tmp +=
  "To melt an ingot into a weapon blank:\n"
  "  melt <ingot> into weapon blank\n"
  "  ex: melt mithril ingot into weapon blank\n"
  "\n"
  "To melt 2 ingots into an armour blank:\n"
  "  melt <ingot 1> and <ingot 2> into armour blank\n"
  "  ex: melt davistone ingot 1 and davistone ingot 2\n"
  "      into armour blank\n"
  "NOTE: The two ingots MUST be of the same material.\n";
  this_player()->more(explode(tmp, "\n"));
  return 1;
}

