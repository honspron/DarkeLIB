#include "/adm/include/clock.h"

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(11);
    set_fast_dev_cost(27);
    set_property("target type", "living");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill may be used to restore lost hit points to a player.  "
"The amount of hp restored is determined by the % skill of the player "
"who is laying on hands.  This skill may be used once per day plus another "
"time for every two levels that the player has.",
	this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  int uses, lvl, wound;

  lvl = (int)from->query_level();
  if (!from->query_property("hand uses"))
      uses = 0;
  else uses = (int)from->query_property("hand uses");
  if((time() - (int)from->query_last_use("lay on hands")) < DAY &&
    uses >= (lvl/2 + 1))
    {
    message("info", sprintf("You may only use this skill %d %s per day.",
                            (lvl/2 + 1),
                            ((lvl/2 + 1)==1)?"time":"times"),
            from);
    remove();
    return;
  } else if((time() - (int)from->query_last_use("lay on hands")) >= DAY) {
    uses = 0;
    from->set_last_use("lay on hands");
  }
  uses++;
  from->set_property("hand uses", uses);
  seteuid(geteuid(this_object()));
  message("info", "You lay hands on "+
          (string)at->query_cap_name()+
          ", healing "+objective(at)+" of "+possessive(at)+" wounds.", from);
  message("info", (string)from->query_cap_name()+
          " lays hands on you, healing you of your wounds!", at);
  message("info", (string)from->query_cap_name()+
          " lays hands on "+(string)at->query_cap_name()+
          ", healing "+objective(at)+" of "+possessive(at)+" wounds.",
          environment(from), ({ from, at }));
  wound = (int)at->query_max_hp() - (int)at->query_hp();
  if(wound <= 0) {
    remove();
    return;
  }
  at->heal(wound * props["skill level"] / 100);
  wound = (wound * props["skill level"] / 100) - wound;
  if(wound > 0) at->add_hp(wound);
  remove();
  return;
}

int can_exceed_max_hp() { return 1; }


          
