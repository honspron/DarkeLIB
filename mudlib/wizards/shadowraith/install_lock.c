inherit "/std/skills/long_term.c";

int skill, ll, ol;
string name;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(25);
    set_fast_dev_cost(60);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to install a lock on a chest, safe, or locker.\n"
"This difficulty of the lock varies with the skill of the craftsman.  "
"This is a long-term skill ('help long-term') and takes much real time to "
"use.  If interrupted, you may pick up the skill again later "
"by 'use'-ing the skill again.\n"
"Syntax: use install lock at <item> <player>\n"
"where player is who the lock will be keyed to.",
	this_player());
}

void skill_func(object from, object at, string arg) {
  int time;
  string tmp,who;
  tmp = lower_case(arg);
  name = tmp;
  who = sprintf("%s/%s/%s", "/adm/save/users", tmp[0..0], tmp);
  if( (file_size(who + ".o") < 0) && (tmp != "all") ) {
    message("info", "That person does not exist.",from);
    remove();
    return;
  }
  if(!at->query_is_locker()) {
    message("info", "This skill must be used on a chest or door.", from);
    remove();
    return;
  }
  if(!at->query_lock_level()) {
    message("info", "That item has a ruined lock which may not be repaired.",from);
    remove();
    return;
  }
  ol = at->query_lock_level();
  skill = props["skill level"];
// At 5% skill, lock level = 12, at 100% lock level = 50.
  ll = skill * 2 / 5 + 10;
  if(ol > (ll + 5)) {
    message("info","This lock is beyond your skill to rework.",from);
    remove();
    return;
  }
  else if(ol > ll) {
    message("info","You try to rework the lock, but end up ruining it.",from);
    at->set_lock_level(1000);
    at->set_lock("locked");
    at->set_key("shadowraith chest key");
    remove();
    return;
  }
  while(shadow(at, 0)) shadow(at, 0)->external_destruct(shadow(at, 0));
  skill = props["skill level"];
  time = 300 + (skill * 15);
  if(time > 1800) time = 1800;
  message("info", "%^CYAN%^%^BOLD%^You begin installing the lock.", from);
  set_work_message("%^CYAN%^You tinker with the lock.");
  start_work(at, from, time);
  return;
}

void finish_work(object from, object at) {
  int i;
  object ob;
    
  message("info", "%^CYAN%^%^BOLD%^You finish installing the lock.",
    from);
  at->set_lock("unlocked");
  at->set_lock_level(ll);
  at->set_key(name+" chest key");
  ob=new("/std/Object");
  ob->set_property("no save", 1);
  ob->set_name("key");
  ob->set_short(capitalize(name) + "'s chest key");
  ob->set_long("This is an iron key designed to work in a chest lock.");
  ob->set_id( ({ "key", "chest key", name + " chest key" }) );
  ob->set_weight(15);
  ob->move(this_player());
  message("info","You craft a key for the new lock.",from);
  remove();
  return;
}
  
