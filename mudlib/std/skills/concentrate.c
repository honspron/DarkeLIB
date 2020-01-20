inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(29);
    set_fast_dev_cost(65);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill can be used to attack while casting a spell.  "
"Type 'use concentrate' to toggle on and off the use of this skill.  "
"If off, you will never attack while casting, as normal.  If on, "
"you will attempt to attack while casting, but you will run a "
"small risk of interrupting your spell."
	, this_player());
}

void skill_func(object from, object at, string arg) {
  if(from->query("concentrate")) {
    from->set("concentrate", 0);
    message("info", "You are no longer concentrating.", from);
    remove();
    return;
  }
  else {
    from->set("concentrate", 1);
    message("info", "You are now concentrating.", from);
    remove();
    return;
  }
}

