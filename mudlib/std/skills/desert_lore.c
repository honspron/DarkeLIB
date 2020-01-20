// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Desert Lore

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(15);
    set_fast_dev_cost(46);
}

void info() {
	string *skills;
	skills = TP->query_all_skills();
	if( (TP->query_class() == "priest of akhamshish") ||
		(member_array("desert lore", skills) != -1) ) {
		message("help", "Desert Lore is used for spells which "
			"deal with the desert.  Terrible winds and "
			"skin shreding sands can be summoned with such "
			"spells.", TP);
	}
	else { message("help", "There is no such skill.", TP); }
}
