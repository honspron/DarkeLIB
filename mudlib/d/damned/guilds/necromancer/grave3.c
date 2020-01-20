#include <std.h>

inherit ROOM;

int corpse_count;

void create() {
	::create();
	corpse_count = 2 + random(3);
	set_property("indoors", 2);
	set_property("light", 1);
	set_short("The Graveyard");
	set_long("This is the southwestern side of the graveyard.  This area seems to be the area that has the most open graves, and the most crows.  The trees in this area seem to be newly planted, as they are all very small and insignificant.");
	set_items(([
	"grave" : "The graves here are mostly open graves, however there still is an abundance of closed graves here.",
	"tree" : "The trees seem innocent and untainted.",
	"crows" : "The crows stand on some of the headstones."
	]));
	set_listen("default", "There isn't a sound to hear.");
	set_smell("default", "The air is stale and looming.");
	set_exits(({
	"/d/damned/guilds/necromancer/grave1",
	"/d/damned/guilds/necromancer/grave6",
	}),({"west", "north"}));
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
