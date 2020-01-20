inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(21);
    set_fast_dev_cost(57);
}

void info() {
message("help",
"This skill allows you to detect when a player is casting a spell, even if "
"he/she can normally cast silently.  Also, if you have the skill at a "
"sufficiently high level, you can even sense what spell they are "
"casting!!!",
this_player());
}

