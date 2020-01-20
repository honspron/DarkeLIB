inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(14);
    set_fast_dev_cost(45);
}

void info() {
message("help",
"This is a spell casting skill that deals with all spells that invlove "
"bringing material objects out of nowhere.  Often these objects are then "
"cast at enemies!",
this_player());
}

