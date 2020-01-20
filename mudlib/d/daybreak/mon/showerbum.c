// /d/nfd/mon/thief

#include <std.h>
#include <daemons.h>
#include <clock.h>

inherit MONSTER;


void create() {
	::create();
      set_name("bum");
      set("id",({"bum", "vagabond", "thief" }) );
	set_level( 10 );
	set_fingers( 5 );
      set("short", "A fat, naked bum");
      set("long","A dingy, fat, naked bum lies drunkenly in a stall. His clothes are nowhere to be seen but have hopefully been burned from the looks of his person.");
	set("race", "high elf");
	set("gender", "male");
	set_body_type("human");
	set_overall_ac( 6 );
	set_skill("melee",60);
	set_skill("knife",60);
	set_skill("perception",60);
	set_skill("pick pocket",95);
	set_skill("stealth",40);
	set_skill("dodge",30);
	set_skill("parry",35);
	set_skill("reverse stroke",55);
	set_stats("dexterity",95);
	set_skill("attack",70);
	set_skill("thrown",30);
	set_class("thief");
}
