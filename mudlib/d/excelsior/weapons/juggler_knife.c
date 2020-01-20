// /wizards/excelsior/weapons/joker_knife
// Excelsior 7-1-96

inherit "/std/weapon";

void create() {
	::create();
	set_name("knife");
	set("id",({"knife","joker knife","juggler knife","juggler's knife","joker's knife",
		"Joker's knife","Joker knife"}));
	set("short","juggling knife");
	set("long","Though originally designed for juggling, its light weight and "+
		"perfect balance only make it all the more deadly!");
	set_weight(70);
	set_value(1000);
	set_ac(5);
	set_wc(15,"cutting");
	set_wc(14,"impaling");
	set_type("knife");
	set_throwable(1);
	set_quality(6);
	set("skill level",60);
	set_hit_bonus(35);
	set_verb("cut");
	set_parry_bonus(40);
		set_material("/metal/catoetine");
}
	
