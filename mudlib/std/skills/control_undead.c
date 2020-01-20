#define UNDEAD_RACES ({ "skeleton", "zombie", "lich", "vampire", \
          "ghoul", "ghost", "undead", "wraith" })
#include "/adm/include/clock.h"

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(13);
    set_fast_dev_cost(40);
    set_property("target type", "living");
    set_property("must be present", 1);
}

void info() {
message("help",
"This is a useful skill which allows you to give simple commands "
"to undead creatures.  The following are supported:\n\n"
"use control undead at <creature> with go <direction>\n"
"  attempts to force a creature to go in <direction>\n"
"use control undead at <creature> with attack <creature 2>\n"
"  attempts to force the undead creature to attack <creature 2>\n"
"use control undead at <creature> with die\n"
"  attempts to banish the undead soul from this plane, \n"
"  killing the creature.",
	this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  int i;
  string arg1, arg2, *tmp;
  
  if((time() - (int)from->query_last_use("control undead")) / MINUTE < 5) {
    message("info", "You must wait a while longer before using this skill.",
        from);
    remove();
    return;
  }
  if(member_array((string)at->query("race"), UNDEAD_RACES) < 0) {
    message("info", "You must use this skill on an undead creature.",
	from);
    remove();
    return;
  }
  from->set_last_use("control undead");
  if(arg) arg1 = (tmp = explode(arg, " "))[0];
  if((i=sizeof(tmp)) >= 2)
    arg2 = implode(tmp[1..(i-1)], " ");
  if(!arg1) {
    message("info", "See 'help skill control undead' for syntax.", from);
    remove();
    return;
  }
  switch(arg1) {
  case "go":
    if(skill_contest(props["skill level"], (int)at->query_stats("constitution") / 2) == 2) {
      message("info", (string)at->query_cap_name() + " resists your control.", from);
      remove();
      return;
    }
    if(member_array(arg2, (string *)environment(at)->query_exits()) < 0) {
      message("info", "There is no such exit in this room.", from);
      remove();
      return;
    }
    at->force_me(arg2);
    break;
  case "attack":
    if(skill_contest(props["skill level"], (int)at->query_stats("constitution")) == 2) {
      message("info", (string)at->query_cap_name() + " resists your control.", from);
      remove();
      return;
    }
    if(!(ob = present(lower_case(arg2), environment(at)))) {
      message("info", "There is no '"+arg2+"' here.", from);
      remove();
      return;
    }
    at->kill_ob(ob, 0);
    break;
  case "die":
    if(skill_contest(props["skill level"], (3*(int)at->query_stats("constitution")/2)) != 1) {
      message("info", (string)at->query_cap_name() + " resists your control.", from);
      remove();
      return;
    }
    at->add_hp(-30 + (int)at->query_hp());
    break;
  default:
    message("info", "See 'help skill control undead' for syntax.", from);
    break;
  }
  remove();
  return;
}
    
