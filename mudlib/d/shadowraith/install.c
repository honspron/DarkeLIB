inherit "/std/skills/long_term.c";
inherit "/std/check_brittle";

int skill;
int set_owner(string str, object ob);

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
"This skill is used to install a lock on a chest or door.\n"
"This difficulty of the lock varies with the skill of the craftsman.  "
"This is a long-term skill ('help long-term') and takes much real time to "
"use.  If interrupted, you may pick up the skill again later "
"by 'use'-ing the skill again.\n"
"Syntax: use install lock at <item>",
	this_player());
}

void skill_func(object from, object at, string arg) {
  int tmp,time;

  if(!at->query_is_locker()) {
    message("info", "This skill must be used on a chest or door.", from);
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
  int i, ll;
    
  message("info", "%^CYAN%^%^BOLD%^You finish installing the lock.",
    from);
// At 5% skill, lock level = 12, at 100% lock level = 50.
  ll = skill * 2 / 5 + 10;
  at->set_lock("unlocked");
  at->set_lock_level(ll);
  message("info","Enter owner's name:",from);
  input_to("set_owner", at);
  remove();
  return;
}

int set_owner(string str, object at) {
    at->set_key(str + " chest key");
    return 1;
}

  
