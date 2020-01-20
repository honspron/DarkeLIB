// Coder: %^YELLOW%^nEv!N%^RESET%^
// Darkemud
// Prayer to Akhamshish

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(15);
    set_fast_dev_cost(46);
}

void info() {
message("help",
"Prayer to Akhamshish is the method by which Priests of Akhamshish cast "
"many of their spells.  Absolute devotion is required of Akhamshish by "
"all of his followers.  In return for such devotion, Akhamshish grants "
"his priests powerful spells of destruction so they may carry his word "
"to the unenlightened.",
this_player());
}
