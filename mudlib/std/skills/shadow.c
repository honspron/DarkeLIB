inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(25);
    set_fast_dev_cost(77);
    set_property("target type", "living");
    set_property("must be present" , 1);
    set_property("prereq", "stalk");
}

void info() {
message("help",
"This is a slightly more useful version of the stalk skill, see 'help "
"skill stalk'.  In addition to moving stealthily, you may shadow a "
"player or monster wherever he/she/it/goes.  Unlike the stalk skill, "
"you stay completely hidden, in addition to moving stealthily.\n"
"    use shadow at diewarzau",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  int flag;

  if(ob = (object)from->query("stealth shad")) {    
    from->set("stealth shad", 0);
    if((string)ob->query_my_skill() == "stalk" ||
       (string)ob->query_my_skill() == "shadow")
       flag = 1;
    ob->external_destruct(ob);
    ob = (object)from->query("stalking");
    if(objectp(ob) && ob->query_followers() &&
       member_array(from, (object *)ob->query_followers()) >= 0) {
      ob->remove_follower(from);
      message("info", "You stop following "+(string)ob->query_cap_name()+
	      ".", from);
    }
    from->set("stalking", 0);
    if(flag) {
      message("my_action", "You are no longer shadowing.", from);
      remove();
      return;
    }
  }
  message("my_action", "You begin to move stealthily, following "+
	  (string)at->query_cap_name()+".", from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/stealth_shadow");
  from->set("stealth shad", ob);
  ob->set_my_skill("shadow");
  ob->set_hide_skill("shadow");
  ob->start_shadow(from);
  at->add_follower(from);
  from->set("stalking", at);
  remove();
  return;
}
