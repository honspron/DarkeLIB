inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(21);
    set_fast_dev_cost(55);
}

void info() {
message("help",
"This skill is quite useful against thieves or the like that wish to "
"use the 'back stab' skill on you.  It allows you to surprise them with "
"an attack before they can harm you!"
	, this_player());
}

