inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(15);
    set_fast_dev_cost(47);
}

void info() {
message("help",
"This spell casting skill deals with death magic in all its forms.  "+
"This ranges from animating undead, to causing areas to decay, to "+
"simple spells of cold.",
this_player());
}

