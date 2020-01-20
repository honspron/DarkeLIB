// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Summon Desert Spirit: Priests of Akhamshish
// Modified from summon_aerial_servant.c
// Pet File: /wizards/nevin/guilds/ak/mon/desert_spirit.c
// Material Components: pinch, /wizards/nevin/guilds/ak/obj/pinch.c

inherit "/std/spells/spell";

object pinch;

void create() {
    	::create();
    	set_property("name","summon desert spirit");
    	set_property("skill","desert lore");
// 57
    	set_property("casting time", 1);
    	set_property("base mp cost", 34);
    	set_property("dev cost", 14);
    	set_property("fast dev cost", 41);
    	set_property("spell level", 2);
    	set_property("moon","luna");
    	set_property("caster message","%^YELLOW%^%^BOLD%^A spinning ball of "
		"wind whizzes around you ready to do your bidding.");
    	set_property("target message","");
    	set_property("observer message","%^YELLOW%^%^BOLD%^$C offers a "
		"prayer to the spirits of the desert.  In response, a "
		"desert spirit comes to the aid of $C.");
    	set_property("spell type",({ }));
    	set_property("no target", 1);
    	set_property("duration", 300);
    	return;
}

void info() {
	string *spells;
	spells = TP->query_all_spells();
	if(member_array("summon desert spirit", spells) != -1) {
		message("help",
			"Prerequisite Spell: Ceremony of Purification\n"
			"Material Component(s): pinch of sand\n\n"
			"Wandering the deserts upon the ever shifting "
			"winds are spirits.  Prone to cause havok and "
			"trouble for those who would dare to intrude "
			"upon their desert home, they can sometimes be "
			"tamed by those who understand their ways.  "
			"They can be used to give a 'tell' to another "
			"player, but asking them to do so will free "
			"them from the magical bounds of this spell.  "
			"This spell may only be cast in the desert.\n\n"
			"Usage: cast *<pow> summon desert spirit\n"
			"Help: tell spirit help\n", TP);
	}
	else {
		message("help",
			"One can only guess what mysterious powers those "
			"who understand the desert have.", TP);
	}
}

void spell_func(object caster, object at, int power, string args, int flag) {
	object ob;
	int i;
	seteuid(getuid());
	if(!(ENV(caster)->query_terrain() == "D") ) {
		message("info", "You may only cast this spell in the desert.",
			caster);
		remove();
		return;
	}
	if(!(pinch = present("sand", caster))) {
		message("info", "A pinch of sand is required to cast "
			"this spell.  The desert spirit zooms away.", caster);
		remove();
		return;
	}
	if(caster->query_spell_level("ceremony of purification") <
		( (props["extra power"])?(power-props["extra power"]):power) ) {
		message("info", "You are unable to control the desert "
			"spirit!  It summons some of its brethen to kill you!",
			caster);
		for(i=0;i<3;i++) {
			ob = new("/wizards/nevin/guilds/ak/mon/desert_spirit");
			ob->set_up(power);
			ob->move(ENV(caster));
			ob->kill_ob(caster, 0);
		}
		remove();
		return;
	}
	ob = new("/wizards/nevin/guilds/ak/mon/desert_spirit");
	ob->set_up(power);
  	ob->move(environment(caster));
	if(!flag)
    		ob->set_owner((string)caster->query_name());
  		ob->set_dur(props["duration"]);
		pinch->remove();
  	if(flag) {
    		message("info", "The desert spirit frees itself from your "
			"spell and attacks you!", caster);
    		message("info", "The desert spirit attacks its summoner!",
	     		ENV(caster), ({caster}) );
    		ob->kill_ob(caster, 0);
  	}
  	remove();
  	return;
}
