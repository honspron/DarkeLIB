inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("charisma");
    set_dev_cost(9);
    set_fast_dev_cost(21);
}

void info() {
message("help",
"This is the skill of trade, allowing you to haggle successfully with "
"shopkeepers and the like.  You will receive more money for sold items "
"and be able to offer less for purchased items without being laughed out "
"of the store.",
this_player());
}

