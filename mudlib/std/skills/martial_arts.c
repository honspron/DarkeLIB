inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(14);
    set_fast_dev_cost(50);
}

void info() {
    message("help", "The ancient art of unarmed combat.  A well-trained " +
	"martial artist may be more deadly with his hands than with a "+
	"weapon!"
	, this_player());
}

