// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Ceremony of Purification: Priests of Akhamshish
// Modified from communion.c

// Moving does not stop spell from continuing
// need to add the information look up table stuff

#include "/adm/include/security.h"
inherit "/std/spells/spell";

object incense, dagger, priest, shad;
int spell_power;

void create() {
	::create();
    	set_property("name","ceremony of purification");
    	set_property("skill","prayer to akhamshish");
    	set_property("casting time", 5);
    	set_property("base mp cost", 15);
    	set_property("dev cost", 7);
    	set_property("fast dev cost", 19);
    	set_property("spell level", 1);
    	set_property("moon","ankh");
    	set_property("caster message",
		"%^YELLOW%^%^BOLD%^You begin a prayer to Akhamshish.");
    	set_property("target message","");
    	set_property("observer message",
		"%^YELLOW%^%^BOLD%^$C begins a prayer to Akhamshish.");
    	set_property("spell type",({ }));
    	set_property("no target", 1);
    	set_property("duration", 180);
    	return;
}

void info() {
	string *spells;
	spells = TP->query_all_spells();
	if(member_array("ceremony of purification", spells) != -1) {
		message("help",
			"Prerequisite Spell: none\n"
			"Material Component(s): incense\n\n"
			"\tThis spell allows the caster to enter a "
			"meditative state while praying to Akhamshish.  "
			"While in this state, the priestess will heal faster "
			"and may recieve a vision from her lord.  "
			"Incense is required to cast this spell.\n\n"
			"Usage: cast *<pow> ceremony of purification\n"
			"Example: cast *1 ceremony of purification\n", TP);
	}
	else {
		message("help", "The inner workings of the Priests of "
			"Akhamshish are not for the unenlightened.", TP);
	}
}

void spell_func(object caster, object at, int power, string args, int flag) {
	if(!(incense = present("incense", caster)) || !(dagger =
		present("dagger", caster)) ) {
		message("info", "You need incense and a dagger to perform "
			"this spell.", caster);
		remove();
		return;
	}
	if(flag) {
		message("info", "You are unable to connect to your lord.", 
			caster);
		remove();
		return;
	}
	seteuid(getuid());
	shad = new("/std/spells/shadows/move_shadow");
	shad->set_move_func( (: call_other, this_object(), "int_skill" :) );
	shad->set_move_arg( ({ caster, ENV(caster) }) );
	shad->start_shadow(caster);
	call_out("ceremony1", 20, caster);
	set_heart_beat(2);
	priest = caster;
	spell_power = power;
  	return;
}

void int_skill(object *arg) {
	if(sizeof(arg) != 2 && !objectp(arg[0])) {
		remove();
		return;
	}
	message("my_action", "By moving you interrupt "
		"the ceremony.", arg[0]);
	message("other_action", (string)arg[0]->query_cap_name()+
		" interrupts the ceremony.", 
		all_inventory(arg[1]), ({arg[0]}) );
	remove();
	return;
}

void heart_beat() {
	if(!objectp(priest)) {
		remove();
		return;
	}
	if(!random(10)) { message("info", "%^YELLOW%^%^BOLD%^You feel the "
		"presence of Akhamshish.", priest); }
	priest->add_hp(random(spell_power + 1));
	priest->add_mp(random(spell_power + 1));
	return;
}

void ceremony1(object caster) {
	message("my_action", "You fall upon your knees "
		"while continuing to chant a prayer to Akhamshish.", caster);
	message("other_action", (string)caster->query_cap_name()+" continues "
		"chanting a prayer to Akhamshish.");
	seteuid(UID_FORCE);
	caster->force_me("say Akhamshish!  Hear my prayer to you!");
	seteuid(getuid());
	call_out("ceremony2", 20, caster);
	return;
}

void ceremony2(object caster) {
	if(!present("incense", caster)) {
		message("info", "You need incense to continue the spell.",
			caster);
		remove();
		return;
	}
	message("my_action", "You light incense to clear your mind.", caster);
	message("other_action", (string)caster->query_cap_name()+" lights "
		"some incense, the smoke rises slowly while forming long "
		"tendrils.", ENV(caster), ({caster}) );
	incense->remove();
	call_out("ceremony3", 20, caster);
	return;
}

void ceremony3(object caster) {
	message("my_action", "You slice a large wound into the palm of your "
		"hand.  The blood drops down the side of your hand and drips "
		"into the burning incense.", caster);
	message("other_action", (string)caster->query_cap_name()+" takes a "
		"dagger and slices a large cut into "+
		caster->query_possessive()+" hand.  The blood mingles with "
		"the burning incense sending a sharp smell around the room.",
		ENV(caster), ({caster}) );
	seteuid(UID_FORCE);
	caster->force_me("say May your blessed word cleanse the world.");
	seteuid(getuid());
	call_out("ceremony4", 20, caster);
	return;
}

void ceremony4(object caster) {
	seteuid(UID_FORCE);
	caster->force_me("say Blessed be Akhamshish!  For you I will gladly "
		"die!");  
	seteuid(getuid());
	message("info", "With the completion of the ceremony of purification "
		"you stand up.", caster);
	message("other_action", (string)caster->query_cap_name()+" opens "
		+caster->query_possessive()+" eyes and breathes in a deep "
		"breath of air.  The ceremony is over.");
	set_heart_beat(0);
	remove();
	return;
}
