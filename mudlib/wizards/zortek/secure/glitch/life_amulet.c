//	Wizard:	 Glitch
//	Amulet - Troll quest
//	amulet.c

#include <std.h>

inherit OBJECT;

void create() {
	::create();
	set_name("amulet");
	set_id( ({ "life amulet","amulet" }) );
	set_short("a brass amulet");
	set_long("This is a large, heavy brass amulet.");
	set_weight(45);
	set_value(12000);
}
