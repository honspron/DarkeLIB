inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(11);
    set_fast_dev_cost(25);
}

void info() {
message("help","This is a skill in armed attack.  It gives you bonuses in the "
"use of all wielded weapons.", this_player());
}

