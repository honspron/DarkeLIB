#include "/adm/include/clock.h"

inherit "/std/skills/skill";

int flag;



void remove();
int clean_up();

void create() {
    ::create();
    set_stat("constitution");
    set_dev_cost(0);
    set_fast_dev_cost(0);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill cannot be developed and is only available to the lycanthropic "
"races (werewolf, weretiger, and werebear).  Using this skill allows you "
"to undergo transformation into animal form when you want, without relying "
"on the phase of the moon or time of day.  It advances a small amount "
"each level.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int res;

  if((time() - (int)from->query_last_use("control change")) / MINUTE < 50) {
    message("info", "You do not have the strength of will to attempt "+
	    "this skill again yet.", from);
    remove();
    return;
  }
  if(from->query_lyc_status()) {
    message("info", "You are already transformed.", from);
    remove();
    return;
  }
  from->set_last_use("control change");
  res = props["skill level"] - random(100);
  if(res < 0) {
    message("info", "You do not succeed in transforming.", from);
    remove();
    return;
  }
  message("info", "You overcome the force of the moon and transform!",
	  from);
  flag = 1;
  from->set("control change", 1);
  call_out("remove_trans", res * 100, from);
  return;
}

int clean_up() {
  if(flag) return 1;
  ::clean_up();
}

void remove() {
  if(flag) return;
  ::remove();
}

void remove_trans(object who) {
  flag = 0;
  who->set("control change", 0);
  remove();
  return;
}
  

