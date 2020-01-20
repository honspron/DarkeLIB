inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("constitution");
    set_dev_cost(21);
    set_fast_dev_cost(64);
}

void info() {
message("help",
"This spell allows you to resist being stunned in combat by hits or spells.  "
"The chance goes down for more powerful stunning attacks.  This skill is always 'on'.",
this_player());
}

