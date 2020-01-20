inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(14);
    set_fast_dev_cost(40);
}

void info() {
message("help",@TEXT
This skill focuses on the narrow realm of remote sensing that allows
a character to gain knowledge that is beyond the normal capacity of
the basic five human senses.  For example, some clairsentients can
"see or hear" (sense) events that are many miles distant, while
others can perceive poison, traps, or _existing_ tangible dangers.
TEXT
,this_player());
}