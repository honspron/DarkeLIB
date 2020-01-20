inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(14);
    set_fast_dev_cost(47);
}

void info() {
message("help",
"This is skill with the magic of chaos, usually employed by chaotic lords.  "+
"Spells in this realm may range from bolts of disruption to spells of harmful "+
"physical alteration.",
this_player());
}

