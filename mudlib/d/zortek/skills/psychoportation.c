inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(15);
    set_fast_dev_cost(41);
}

void info() {
message("help",@TEXT
Psychoportive powers move characters or creatures (living) from one
location to another _without_ crossing space.  The traveler simply
ceases to exist in one location, and begins to exist somewhere else.
Rumors exist of probability and interplanar travel, but even the
most astute sages have failed to find proof.
TEXT
,this_player());
}