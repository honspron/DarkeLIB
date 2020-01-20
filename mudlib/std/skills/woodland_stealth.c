inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(9);
    set_fast_dev_cost(25);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill works similarly to the 'stealth' skill (see 'help skill stealth')."
"  However, it is only effective in wooded areas and jungle, as this skill "
"represents training in hiding one's self among trees and other foliage.",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;

  if(ob = (object)from->query("woodland shad")) {
    message("my_action", "You are no longer in woodland stealth.", from);
    ob->external_destruct(ob);
    from->set("woodland shad", 0);
    remove();
    return;
  }
  message("my_action", "You begin to look for some trees to sneak behind.", 
	  from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/woodland_shadow");
  from->set("woodland shad", ob);
  ob->start_shadow(from);
  remove();
  return;
}

