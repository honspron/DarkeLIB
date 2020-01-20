inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(15);
    set_fast_dev_cost(46);
}

void info() {
message("help",
"Prayer is a powerful form of magic practiced by clerics and priests.  "+
"The spells involved include healing, protection, warding, and scrying, "+
"combined with minor illiusions and summoning.",
this_player());
}

