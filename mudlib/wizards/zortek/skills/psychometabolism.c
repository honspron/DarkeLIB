inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(16);
    set_fast_dev_cost(38);
}

void info() {
message("help",@TEXT
Psychometabolic powers affect the body.  Self-awareness, healing,
and shape-changing are just a few of the complex metabolic functions
that are governed by this skill.
TEXT
,this_player());
}