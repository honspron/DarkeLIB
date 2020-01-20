// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Tssn'ri
// 10/02/96

#include <std.h>

inherit MONSTER;

void create() {
	string var;
	::create();
	set_name("tssn'ri");
	set_id( "tssn'ri" );
	set("race", "demon");
	set_body_type("winged-humanoid");
	set_level(10);
	set("short", "A winged tssn'ri");
	set_long(
		"From the very pits of Marghuul, the the Tssn'ri are the "
		"shock troops of the Darke Lord.  With razor sharp claws "
		"it rakes at the air before you."
	);
	set_property("physical resistance", ([ "default": 25 ]) );
	set_overall_ac(44);
	set_max_hp(1000);
	set_hp(1000);
	set_property("enhance criticals", ([ "holy": 2 ]) );
	set_property("melee damage", ([
		"slashing": 30,
		"crushing": 10
	]) );
	set_emotes(5, ({
		"The tssn'ri releases a blood curdling scream!",
		"Blood drips from the fangs of the tssn'ri.",
		"A voice in your head tells you, 'DIE.  DIE.  DIE. DIE...'"
	}), 0);
	set("aggressive", 1);
	set_property("gang bang", 0);
	call_out("crumble_me", 300);
}

void crumble_me() { TO->die(); }

void heart_beat() {
	object who;
	::heart_beat();
	who = TO->query_current_attacker();

	if(!who) return;
	if(!present(who)) return;
	if(random(100) < 10) {
		if(who->query_level() > random(30) ) { return; }
		message("info", "The tssn'ri screams a cry so foul and "
			"terrible that you freeze in terror!", who);
		message("info", "The tssn'ri screams at "+who->
			query_cap_name()+"!", ENV(who), ({who}) );
		who->set_paralyzed(6, "You can only shake and quiver in "
			"fear!");
		return;
	}
}

void die(object who) {
	message("info", "The tssn'ri crumbles to dust...", ENV(TO));
	if(random(10) == 0) {
		message("info", "From the dust emerges another tssn'ri!",
			ENV(TO));
		new("/d/damned/guilds/chaotic-lord/tssnri")->move(ENV(TO));
	}
	::die(who);
	return;
}
