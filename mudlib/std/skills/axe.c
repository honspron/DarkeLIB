inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(5);
    set_fast_dev_cost(15);
}

void info() {
message("help","This is skill with hand axes and other one-handed axes."
	, this_player());
}

