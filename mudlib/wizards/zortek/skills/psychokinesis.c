inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(15);
    set_fast_dev_cost(39);
}

void info() {
message("help",@TEXT
Psychokinetic powers move objects--from molecules to mountains--
across spacial distances.  A psychokineticist can throw a rock
without touching it, or agitate molecules in a piece of paper
until it bursts into flames.
TEXT
,this_player());
}