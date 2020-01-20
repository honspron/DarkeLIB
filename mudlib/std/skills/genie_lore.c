// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Genie Lore

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(15);
    set_fast_dev_cost(46);
}

void info() {
	if(TP->query_class() == "priest of akhamshish") {
		message("help", "Ages ago, Akhamshish made a pact with "
			"the greater genie powers.  This pact allows the "
			"Priests of Akhamshish to summon genies when in "
			"need.  This skill allows you to summon and "
			"control the various forms of genies.", TP);
	}
	else {
		message("help", "It has been said that the Priests of "
			"Akhamshish are able to summon and control the "
			"capricious and often dangerous genies that "
			"roam the world and beyond.  Whether such "
			"rumors are truth or myth is unknown.", TP);
	}
}
