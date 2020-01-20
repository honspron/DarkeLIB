inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(8);
    set_fast_dev_cost(18);
}

void info() {
message("help",
"This skill is used to spot hidden objects, as the name suggests.  The "
"object can be anything from a hidden treasure to a hiding thief!",
this_player());
}

