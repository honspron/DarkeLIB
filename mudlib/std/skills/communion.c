#include "/adm/include/security.h"
#include "/adm/include/clock.h"

inherit "/std/skills/skill";

object wine;
object bread;
object priest;
object shad;

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(7);
    set_fast_dev_cost(19);
    set_property("prereq", "lay on hands");
    set_property("no target", 1);
}

void info() {
message("help",
"Using this skill starts a ceremony which lasts for a few minutes.  "+
"All who are in the room while you are performing the ceremony heal more "+
"quickly and gain mp more rapidly due to the divine presense invoked.  "+
"Greater skill allows you to perform the ceremony for a greater amount of "+
"time.",
this_player());
}

void skill_func(object from, object at, string arg) {

  if((time() - (int)from->query_last_use("communion")) / HOUR < 1) {
    message("info", "You may only use this skill once per hour "+
	    "(mud time).", from);
    remove();
    return;
  }
  if(!(wine = present("wine", from)) || !(bread = present("bread",
     							  from))) {
    message("info", "You must have bread and wine to perform the "+
	    "ceremony.", from);
    remove();
    return;
  }
  from->set_last_use("communion");
  message("my_action", "%^CYAN%^You begin the ceremony.", from);
  message("other_action", (string)from->query_cap_name() +
	  " begins the ceremony of holy communion.",
	  all_inventory(environment(from)),
	  ({ from }));
  seteuid(getuid());
  shad = new("/std/spells/shadows/move_shadow");
  shad->set_move_func( (: call_other, this_object(), "int_skill" :) );
  shad->set_move_arg( ({ from, environment(from) }) );
  shad->start_shadow(from);
  priest = from;
  call_out("communion1", 10, from);
  set_heart_beat(2);
  return;
}

void int_skill(object *arg) {
  if(sizeof(arg) != 2 && !objectp(arg[0])) {
    remove();
    return;
  }
  message("my_action", "%^CYAN%^By moving, you interrupt the ceremony.",
	  arg[0]);
  message("other_action", (string)arg[0]->query_cap_name() +
	  " interrupts the ceremony.",
	  all_inventory(arg[1]),
	  ({ arg[0] }) );
  remove();
  return;
}

int living_filter(object what) { return living(what); }

void heart_beat() {
  object *all_here;
  int i;

  if(!objectp(priest)) {
    remove();
    return;
  }
  all_here = filter_array(all_inventory(environment(priest)), "living_filter",
			  this_object());
  if(!random(10))
    message("info", "%^BLUE%^You feel a divine presence.", all_here);
  all_here->add_hp(random(8)+1);
  all_here->add_mp(random(8)+1);
  return;
}

void communion1(object from) {
  message("my_action", "%^CYAN%^You pass wine to all around.",
	  from);
  message("other_action", (string)from->query_cap_name() +
	  " gives you a sip of wine.",
	  all_inventory(environment(from)),
          ({ from }));
  seteuid(UID_FORCE);
  from->force_me("say The blood of the Lord.");
  seteuid(getuid());
  wine->empty();
  call_out("communion2", 20, from);
  return;
}

void communion2(object from) {
  message("my_action", "%^CYAN%^You break bread and pass a piece to each "+
	  "person.", from);
  message("other_action", (string)from->query_cap_name() +
          " passes a piece of bread to you.",
	  all_inventory(environment(from)),
          ({ from }));
  seteuid(UID_FORCE);
  from->force_me("say The body of the Lord.");
  seteuid(getuid());
  bread->remove();
  call_out("chant", 10, from, (1+random((int)props["skill level"]) / 5));
  return;
}

void chant(object from, int time) {
  if(time <= 0) {
    seteuid(UID_FORCE);
    from->force_me("say The ceremony is concluded.");
    seteuid(getuid());
    message("other_action", (string)from->query_cap_name() +
	    " ends the communion ceremony.",
	    all_inventory(environment(from)),
            ({ from }));
    set_heart_beat(0);
    remove();
    return;
  }
  time--;
  from->add_exp((25+random(25)) * (int)from->query_level());
  seteuid(UID_FORCE);
  switch(random(4)) {
  case 0:
    from->force_me("say Let us pray.");
    break;
  case 1:
    from->force_me("say Oh Lord, heal us, for we are weary of battle.");
    break;
  case 2:
    from->force_me("say Give thanks for the healing presence of the Lord.");
    break;
  case 3:
  default:
    from->force_me("say Allow your souls to be cleansed.");
  }
  seteuid(getuid());
  call_out("chant", 10, from, time);
  return;
}
