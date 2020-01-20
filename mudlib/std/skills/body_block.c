inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("strength");
    set_dev_cost(9);
    set_fast_dev_cost(29);
}

void info() {
message("help",
"This skill is extremely important for party leaders.  It allows a party "
"leader to block an attacking monster that may want to whack other party "
"members who are throwing daggers, casting spells, etc.",
this_player());
}

