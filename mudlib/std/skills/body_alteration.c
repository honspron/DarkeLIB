inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(13);
    set_fast_dev_cost(40);
}

void info() {
message("help",
"Body Alteration is a realm of magic which deals with all spells affecting "+
"the physical body.  Clerics also practice these magics.  Healing and "+
"harming fall under prayer however, since that is of a spiritual, not "+
"physical nature.",
this_player());
}

