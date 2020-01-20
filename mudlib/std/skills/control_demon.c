inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(21);
    set_fast_dev_cost(52);
    set_property("prereq", "chaos magic");
}

void info() {
message("help",
"This skill allows you to exert your will over magical demons.  Very useful "
"if you intend to summon any.",
this_player());
}

