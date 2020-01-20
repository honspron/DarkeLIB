inherit "/std/skills/skill";

void skill_func(object from, object at, string arg) {
  object shad;

  seteuid(getuid());
  if(from->query_casting()) {
    message("info", "You may not use this skill while casting.", from);
    remove();
    return;
  }
  if(shad = (object)from->query("ele shadow"))
    shad->external_destruct(shad);
  shad = new("/std/spells/shadows/ele_shadow");
  shad->set_element(props["element"]);
  shad->start_shadow(from);
  from->set("ele shadow", shad);
  message("info", "You are now practicing the elemental college of "+
	  capitalize(props["element"]) + ".", from);
  remove();
  return;
}

void create() {
  ::create();
  set_property("no target", 1);
  set_stat("intelligence");
  return;
}

void info() {
  message("help",
"This is skill with elemental magic in the "+ props["element"] +
" college.  Use this skill to change your elemental casting to this "+
"college.  Your skill in the college will modify your elementalism skill "+
"accordingly.",
this_player());
}

