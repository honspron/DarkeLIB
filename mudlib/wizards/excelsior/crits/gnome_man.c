// /wizards/excelsior/crits/gnome_man

inherit "std/monster";

object who;

void create() {
	::create();
	set_name("gremlin");
	set("id",({"gnome man","gremlin","gnome","man","creature",
		"gnome creature","gnome_man"}));
	set_level(17);
	set("short","A crafty little gnome creature");
	set("long","This gremlin creature looks very malicious and evil. It "+
		"looks like it has nothing better to do then cause pain and harm.");
	set("race","gremlin");
	set_gender("neuter");
	set_body_type("human");
	set_overall_ac(24);
	set_melee_damage( (["cutting":11,"impaling":12,"holy":3]));
/*
	set_combat_chance(60);
	set_skill("concentration",80);
	set_skill("prayer",50);
	set_skill("conjuration",50);
	set_skill("body alteration",62);
	add_spell("heal","$(ME)");
	add_spell("meteor storm","$A");
	add_spell("fireball","$A");
	add_spell("ice dagger","$A");
	add_spell("killing cloud","$A");
	add_spell("haste","$(ME)");
	set_spell_level("ice dagger",4);
	set_spell_level("fireball",5);
	set_spell_level("meteor strom",2);
	set_spell_level("killing cloud",3);
	set_spell_level("heal",3);
	set_spell_level("haste",2);
	set_skill("melee",89);
*/
	call_out("reset",1);
}

void reset() {
	::reset();
	force_me("use concentration");
}

void target(object target,object from) {
	who = target;
	kill_ob(target,0);
}

void heart_beat() {
	::heart_beat();
	if(!who) return;
	if(!present(who) && environment(who)) {
		message("info","%^YELLOW%^%^BOLD%^The gremlin scurries off after its prey!",
			environment());
		this_object()->move(environment(who));
		message("info","%^YELLOW%^%^BOLD%^A gremlin scurries into the room in hot "+
			"persuit of its prey!",environment());
	}
}
