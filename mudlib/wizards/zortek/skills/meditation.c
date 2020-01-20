#include <security.h>
#include <clock.h>

inherit "/std/skills/skill";

object seer;
object shad;

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(7);
    set_fast_dev_cost(19);
    set_property("no target", 1);
}

void info() {
message("help",@TEXT
TEXT
,this_player());
}

void skill_func(object from, object at, string arg) {

  if((time() - ((int)from->query_last_use("meditation")) / HOUR)-
    from->query_level() < 1) {
    message("info", "You may only effectively meditate once per hour "+
	    "minus your level in minutes (mud time).", from);
    remove();
    return;
  }
  from->set_last_use("meditation");
  message("my_action", "%^CYAN%^You get comfortable and prepare to meditate.", from);
  message("other_action", (string)from->query_cap_name() +
	  " appears to relax.",	all_inventory(environment(from)),({ from }));
  seteuid(getuid());
  shad = new("/std/spells/shadows/move_shadow");
  shad->set_move_func( (: call_other, this_object(), "int_skill" :) );
  shad->set_move_arg( ({ from, environment(from) }) );
  shad->start_shadow(from);
  seer = from;
  call_out("meditation1", 10, from);
  set_heart_beat(2);
  return;
}

void int_skill(object *arg) {
  if(sizeof(arg) != 2 && !objectp(arg[0])) {
    remove();
    return;
  }
  message("my_action", "%^CYAN%^By moving, you disrupt your meditation.", arg[0]);
  message("other_action", (string)arg[0]->query_cap_name() + " disrupts "+
    (string)arg[0]->query_possessive()+" meditation.", all_inventory(arg[1]),
	  ({ arg[0] }) );
  remove();
  return;
}

int living_filter(object what) { return living(what); }

void heart_beat() {
  object *all_here;
  int i;

  if(!objectp(seer)) {
    remove();
    return;
  }
  all_here = filter_array(all_inventory(environment(seer)), 
    "living_filter", this_object());
  if(!random(10))
    message("info", "%^BLUE%^You feel refreshed.", seer);
  all_here->add_hp(1);
  all_here->add_mp(random(10)+10);
  return;
}

void meditation1(object from) {
  message("my_action", "%^CYAN%^You begin a quiet mantra.",from);
  message("other_action", (string)from->query_cap_name() +
	  " begins a quiet mantra.", all_inventory(environment(from)), ({ from }));
  seteuid(UID_FORCE);
  from->force_me("moan");
  seteuid(getuid());
  delayed_call("meditation2", 20, from);
  return;
}

void meditation2(object from) {
  message("my_action", "%^CYAN%^You enter a higher state of consciousness.", from);
  message("other_action", (string)from->query_cap_name() +
    "'s eyes appear to glaze over.", all_inventory(environment(from)), ({ from }));
  seteuid(UID_FORCE);
  from->force_me("meditate deeply");
  seteuid(getuid());
  delayed_call("mantra", 10, from, (1+random((int)props["skill level"]) / 5));
  return;
}

void chant(object from, int time) {
  if(time <= 0) {
    seteuid(UID_FORCE);
    from->force_me("shudder");
    seteuid(getuid());
    message("other_action", (string)from->query_cap_name() +
	    " appears alert and refreshed, but maintains a distant gaze.",
	    all_inventory(environment(from)),({ from }));
    set_heart_beat(0);
    remove();
    return;
  }
  time--;
  from->add_exp((25+random(100)) * (int)from->query_level());
  seteuid(UID_FORCE);
  switch(random(4)) {
  case 0:
    from->force_me("mumble");
    break;
  case 1:
    from->force_me("emoan");
    break;
  case 2:
    from->force_me("hum quietly");
    break;
  case 3:
  default:
    from->force_me("relax somberly");
  }
  seteuid(getuid());
  call_out("chant", 10, from, time);
  return;
}
