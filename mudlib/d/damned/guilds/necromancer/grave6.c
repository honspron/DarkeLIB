#include <std.h>

inherit ROOM;

int corpse_count;

void create() {
	::create();
	corpse_count = 2 + random(3);
	set_property("indoors", 2);
	set_property("light", 1);
	set_short("The Graveyard");
	set_long("This is the northeastern edge of the graveyard.  The surrounding cemetary is rimmed with a wall that fades into the forest towards the east.  The gravestones seem lively as the are covered with beautiful mosses and mushrooms.  To the northwest is a large mausoleum.");
	set_items(([
	"wall" : "The walls fade into the forest to the east.",
	"moss" : "The moss is bright green.",
	"mushroom" : "The mushrooms are beautiful and small.",
	"mausoleum" : "The mausoleum overlooks the graveyard."
	]));
	set_listen("default", "There isn't a sound to hear.");
	set_smell("default", "The air is stale and looming.");
	set_exits(({
	"/d/damned/guilds/necromancer/grave5",
	"/d/damned/guilds/necromancer/grave3",
	}),({"west", "south"}));
}


int dig_corpse(){
	int chk_per;
object ob;
if(corpse_count <= 0){
	write("You don't find any corpses, maybe wait until more people die.");
return 1;
}
chk_per = this_player()->query_skill("perception");
if((random(5)+chk_per)<13){
	write("You don't find any corpses.");
return 1;
}
	corpse_count--;
say(this_player()->query_cap_name()+" digs for some corpses.");
write("You search for corpses.");
switch(random(10)){
	case 0:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Ralph");
		ob->move(this_object());
		write("You found a corpse.");
		break;
	case 1:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Bishop");
		ob->move(this_object());
		write("You found a corpse.");
		break;
	case 2:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Gary");
		ob->move(this_object());
		write("You found a corpse!");
		break;
	case 3:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Shirely");
		ob->move(this_object());
		write("You found a corpse.");
		break;
	case 4:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Karen");
		ob->move(this_object());
		write("You found a corpse.");
		break;
	case 5:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Linda");
		ob->move(this_object());
		write("You found a corpse.");
		break;
	case 6:ob=new("/std/obj/mon_corpse");
		ob->set_level(1);
		ob->set_name("Carl");
		ob->move(this_object());
		write("You found a corpse.");
		break;
	case 7:ob=new("/std/obj/mon_corpse");
		ob->set_level(2);
		ob->set_name("Kim");
		ob->move(this_object());
		write("You found a corpse!");
		break;
	case 8:ob=new("/std/obj/mon_corpse");
		ob->set_level(3);
		ob->set_name("Theo");
		ob->move(this_object());
		write("You found a corpse!!");
		break;
	case 9:ob=new("/wizards/blial/necromancer/skeleton");
		ob->set_up(1);
		ob->move(this_object());
		write("You found a skeleton!");
		break;
}
return 1;
}
