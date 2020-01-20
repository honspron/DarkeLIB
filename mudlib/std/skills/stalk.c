inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(15);
    set_fast_dev_cost(49);
    set_property("target type", "living");
    set_property("must be present" , 1);
}

void info() {
message("help",
"This is a slightly more useful version of the stealth skill, see 'help "
"skill stealth'.  In addition to moving stealthily, you may shadow a "
"player or monster wherever he/she/it/goes.\n"
"    use stalk at diewarzau",
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
      message("my_action", "You are no longer stalking.", from);
      remove();
      return;
    }
  }
  message("my_action", "You begin to move stealthily, following "+
	  (string)at->query_cap_name()+".", from);
  seteuid(getuid());
  ob = new("/std/spells/shadows/stealth_shadow");
  from->set("stealth shad", ob);
  ob->set_my_skill("stalk");
  ob->start_shadow(from);
  at->add_follower(from);
  from->set("stalking", at);
  remove();
  return;
}
