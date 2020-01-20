inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(25);
    set_fast_dev_cost(78);
    set_property("no target", 1);
    set_property("prereq", "stealth");
}

void info() {
message("help",
"This skill is like a combination between the stealth and hide in "
"shadows skills.  You may move stealthily, plus you will not be noticed if "
"a player looks about the room.",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;

  if(ob = (object)from->query("stealth shad")) {
    if((string)ob->query_my_skill() == "invisibility art") {
      message("my_action", "You are no longer using invisibility art.",
              from);
      ob->external_destruct(ob);
      remove();
      return;
    }
    ob->external_destruct(ob);
    from->set("stealth shad", 0);
  }
  message("my_action", "You begin to move invisibly.", from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/stealth_shadow");
  from->set("stealth shad", ob);
  ob->set_my_skill("invisibility art");
  ob->set_hide_skill("invisibility art");
  ob->start_shadow(from);
  remove();
  return;
}
