#include <clock.h>

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("strength");
    set_dev_cost(10);
    set_fast_dev_cost(27);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill is used to obtain wood from trees (natch).  It must be used "
"in the forest, and you must be wielding some sort of axe or polearm.  "
"Yes, you can chop down a tree with a halberd if that's all you have.\n"
"Usage: use lumberjack",
	this_player());
}


void skill_func(object from, object at, string arg) {
  object *weap;
  int i, flag;
   
  if((time() - (int)from->query_last_use("lumberjack")) / MINUTE < 5)
    {
    message("info", "You may only use this skill once every 5 mud minutes.", from);
    remove();
    return;
  }
  if(!environment(from)->query_terrain() ||
    lower_case((string)(environment(from)->query_terrain())) != "f") {
    message("info", "You must use this skill in the forest.", from);
    remove();
    return;
  }
  i = sizeof(weap = (object *)from->query_wielded());
  flag = 0;
  while(i--) if((string)weap[i]->query_type() == "axe" ||
      (string)weap[i]->query_type() == "two handed polearm") flag = 1;
  if(!flag) {
    message("info", "You must wield an axe or polearm to use this skill.", from);
    remove();
    return;
  }
  from->set_last_use("lumberjack");
  message("info", "%^CYAN%^%^BOLD%^You start chopping.", from);
  message("info", "%^CYAN%^"+(string)from->query_cap_name() +
      " starts chopping down a tree.", environment(from),
      ({ from }));
  call_out("chop_down", 5, from, environment(from));
  return;
}

void chop_down(object from, object env) {
  object ob;
  
  if(env != environment(from)) {
    message("info", "You have moved while attempting to cut down a tree.  "+
          "Your skill fails.", from);
    remove();
    return;
  }
  message("info", "%^CYAN%^"+(string)from->query_cap_name() +
      " finishes chopping down a tree.", from);
  if(random(100) >= props["skill level"]) {
    message("info", "The tree you chop down fails to yield any weapon-quality wood.", from);
    remove();
    return;
  }
  message("info", "You select a board which will fashion a fine weapon.", from);
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/misc/board");
  ob->move(from);
  return;
}

          
