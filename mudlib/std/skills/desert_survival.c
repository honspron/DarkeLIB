// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Desert Survival

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("constitution");
    set_dev_cost(7);
    set_fast_dev_cost(19);
}

void info() {
	message("help", "This spell allows you to survive the harsh "
		"desert climate.  Those who do not have this skill "
		"will face great risks travelling through the desert "
		"during the day or during sand storms.", TP);
}
