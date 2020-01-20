inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(15);
    set_fast_dev_cost(47);
}

void info() {
message("help",
"This college of magic deals with spells that affect magic itself.  "+
"Spells which counter and reflect others, as well as magic resistance and "+
"spell shields fall under this category.",
this_player());
}

