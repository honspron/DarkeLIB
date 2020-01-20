inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(12);
    set_fast_dev_cost(37);
    set_property("no target", 1);
    set_property("prereq", "hide in shadows");
}

void info() {
message("help",
"This skill allows you to sneak about unnoticed.  Using the skill toggles "+
"it on and off.  Keep in mind that players and monsters with good perception "+
"skill can still see you.",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;

  if(ob = (object)from->query("stealth shad")) {
    if((string)ob->query_my_skill() == "stealth") {
      ob->external_destruct(ob);
      message("my_action", "You are no longer in stealth.", from);
      remove();
      return;
    }
    ob->external_destruct(ob);
    from->set("stealth shad", 0);
  }
  message("my_action", "You begin to move stealthily.", from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/stealth_shadow");
  from->set("stealth shad", ob);
  ob->start_shadow(from);
  remove();
  return;
}
