inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(18);
    set_fast_dev_cost(54);
    set_property("no target", 1);
    set_property("prereq", "stealth");
}

void info() {
message("help",
"This is a rather entertaining skill that allows you to disguise yourself "
"as another player.  This can be quite useful in avoiding detection and "
"revenge!\n"
"Usage:      use disguise at <player>    Disguises you as <player>\n"
"            use disguise                Removes the disguise.\n",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  object pl;

  if(ob = (object)from->query("disguise shad")) {
    message("my_action", "You remove your disguise.", from);
    ob->external_destruct(ob);
    message("other_action", (string)from->query_cap_name()+
	    " removes a disguise.",
	    environment(from), ({ from }));
    from->set("disguise shad", 0);
    if(!arg || !strlen(arg)) {
      remove();
      return;
    }
  }
  if(!arg) {
    message("info", "You have no disguise on.", from);
    remove();
    return;
  }
  pl = find_player(lower_case(arg));
  if(!pl) {
    message("info", "Couldn't find '"+arg+"' on the mud.", from);
    remove();
    return;
  }
  if(wizardp(pl)) {
    message("info", "You may not disguise yourself as a wizard.", from);
    remove();
    return;
  }
  message("my_action", "You disguise yourself as "+(string)pl->
	  query_cap_name()+".",
	  from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/disguise_shad");
  from->set("disguise shad", ob);
  ob->set_my_skill(props["skill level"]);
  ob->set_target(from,(string)pl->query_name());
  ob->set_new_short((string)pl->query_short());
  ob->set_new_cap_name((string)pl->query_cap_name());
  ob->start_shadow(from);
  remove();
  return;
}

