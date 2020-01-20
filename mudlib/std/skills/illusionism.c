inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(15);
    set_fast_dev_cost(47);
}

void info() {
message("help",
"This spell casting skill allows you to deal in the arts of illusion.  "+
"The spells governed by this skill may range from spells of deception and "+
"disguise to spells of illusionary attack!",
this_player());
}

