#include "/adm/include/clock.h"
#define MINERALS ({ "iron", "eog","mithril", "elrodnite", \
       "planite", "steel", "laen", "mabril", "javednite", \
        "iysaughton", "davistone", "catoetine" })

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(11);
    set_fast_dev_cost(33);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill is used to find minerals around the world map in order "
"to mine them.  You simply 'use' the skill anywhere on the world map "
"and a report, whose accuracy depends on your skill, will be given.",
	this_player());
}

void skill_func(object from, object at, string arg) {
  int i;
  object env;
  string *descs;

  if(!archp(from))

  if((time() - (int)from->query_last_use("prospecting")) / MINUTE < 10)
    {
    message("info", "You are weary of prospecting and must rest for a few minutes.", from);
    remove();
    return;
  }
  env = environment(from);
  from->set_last_use("prospecting");
  if(!environment(from)->query_terrain()) {
    message("info", "You must use this skill outside on the world map.",
        from);
    remove();
    return;
  }
  message("info", "%^CYAN%^You begin searching the dirt for traces of minerals.", from);
  message("info", "You find:", from);
  i = sizeof(MINERALS);
  descs = ({});
  if(props["skill level"] > 100) props["skill level"] = 100;
  while(i--) {
    switch((random(2)?(300-props["skill level"]*2):(random(props["skill level"]))) * (int)env->query_mineral(MINERALS[i])
          / 100 - 1) {
    case -100..2:
      break;
    case 3..5:
      descs += ({ "Traces of "+MINERALS[i] });
      break;
    case 6..10:
      descs += ({ "A few nuggets of "+MINERALS[i] });
      break;
    case 11..20:
      descs += ({ "A small amount of "+MINERALS[i] });
      break;
    case 21..35:
      descs += ({ "A decent amount of "+MINERALS[i] });
      break;
    case 36..50:
      descs += ({ "Quite a bit of "+MINERALS[i] });
      break;
    case 51..75:
      descs += ({ "A good deal of "+MINERALS[i] });
      break;
    case 76..150:
      descs += ({ "Lots of "+MINERALS[i] });
      break;
    case 151..10000:
      descs += ({ "Tons of "+MINERALS[i] });
      break;
    }
  }
  message("info", format_page(descs, 2), from);
  remove();
  return;
}

