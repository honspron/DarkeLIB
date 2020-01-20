#include <move.h>
#include <security.h>

inherit "/std/skills/skill.c";

object mage,shad,item1,item2,item3;

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(9);
    set_fast_dev_cost(26);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
    message("help", @TEXT
This skill is used to prepare items to receive animating power
from a MindMage.  In order to prepare an item properly, you must
have in your possession the components necessary for the power
level you are preparing the item to receive.  The components
range from simple an inexpensive to gastly rare and expensive.
    Components for a "basic" preparation include:
        sea salt, incense, and filtered water
A higher skill level lets you prepare an item more quickly.
SYNTAX: use prepare item at dagger
TEXT
,this_player());
}

void skill_func(object from, object at, string arg) {
    int prep_level;
    string *items;

    prep_level = (int)at->query_property("prepared");    
    switch(prep_level) {
      case 0 :  
        items = ({ "sea salt","incense","filtered water" });
        break;
      case 1 :
        items = ({ "rock salt","rose petals","slug slime" });
        break;
      case 2 :
        items = ({ "black sand","sulfur","coconut milk" });
        break;
      case 3 :
        items = ({ "ground obsidian","dragon dung","grain alcohol" });
        break;
      case 4 :
        items = ({ "pearl powder","lemon peel","elven urine" });
        break;
      case 5 :
        items = ({ "diamond dust","saffron oil","virgin tears" });
        break;
      default:
        message("info","You are unable to prepare this item any further.", from);
        remove();
        return;
    }
    if(!(item1 = present(items[0], from)) ||
       !(item2 = present(items[1], from)) ||
       !(item3 = present(items[2], from))) {
      message("info", 
              "You do not have all the items you need to prepare the "+
              at->query_name()+".", from);
      remove();
      return;
    }
    seteuid(getuid());
    message("info", "%^CYAN%^You begin to prepare the "+at->query_name()+".",from);
    message("info", "%^CYAN%^"+(string)from->query_cap_name() +
      " appears to be doing something with a "+at->query_name()+".",
       environment(from), ({ from }));
#if 0
    shad = new("/std/spells/shadows/move_shadow");
    shad->set_move_func( (: this_object(), "int_skill" :) );
    shad->set_move_arg( ({ from, environment(from) }) );
    shad->start_shadow(from);
#endif
    mage = from;
    if(props["skill level"] > 125) props["skill level"] = 125;
    call_out("prepare1", 150-props["skill level"], from, at);
    return;
}
  
void prepare1(object from, object at) {
  message("my_action", "%^CYAN%^You sprinkle the "+
          (string)item1->query_short()+" full circle around you.",
          from);
  message("other_action", (string)from->query_cap_name() +
          " sprinkles "+(string)item1->query_short()+
          " full circle about "+(string)from->query_objective()+"self.",
          all_inventory(environment(from)),
          ({ from }));
  seteuid(UID_FORCE);
  from->force_me("say Er Ist...AhhhhhhUooom.");
  seteuid(getuid());
  item1->remove();
  if(props["skill level"] > 125) props["skill level"] = 125;
  call_out("prepare2", 150-props["skill level"], from, at);
  return;
}

void prepare2(object from, object at) {
  message("my_action", "%^CYAN%^You begin to burn the "+
          (string)item2->query_short()+" and it starts to smoke aromatically.",
          from);
  message("other_action", (string)from->query_cap_name() +
          " begins to burn some "+(string)item2->query_short()+
          " and it starts to smoke aromatically.",
          all_inventory(environment(from)),
          ({ from }));
  seteuid(UID_FORCE);
  from->force_me("say Du Bist...OooooAaammm.");
  seteuid(getuid());
  item2->remove();
  if(props["skill level"] > 125) props["skill level"] = 125;
  call_out("prepare3", 150-props["skill level"], from, at);
  return;
}

void prepare3(object from, object at) {
  message("my_action", "%^CYAN%^You bathe the "+
          (string)at->query_name()+" in the "+
          (string)item3->query_short()+
          " and begin to concentrate intently.",
	  from);
  message("other_action", (string)from->query_cap_name() +
          " places a "+(string)at->query_name()+
          " in a bath of "+(string)item3->query_short()+
          " and begins to concentrate intently.",
          all_inventory(environment(from)),
          ({ from }));
  seteuid(UID_FORCE);
  from->force_me("say Ich Bin...AhhhhhhUooom.");
  seteuid(getuid());
  item3->remove();
  if(props["skill level"] > 125) props["skill level"] = 125;
  call_out("prepare_done", 150-props["skill level"], from, at);
  return;
}
void prepare_done(object from, object at) {
  int wibble;
  message("my_action", "%^CYAN%^You have finished preparing your "+
          (string)at->query_name()+".",
          from);
  message("other_action", (string)from->query_cap_name() +
          " finishes preparing "+(string)from->query_possessive()+
          " "+(string)at->query_name()+".",
          all_inventory(environment(from)),
          ({ from }));
  seteuid(UID_FORCE);
  from->force_me("say Will is the way...It is done.");
  seteuid(getuid());
  wibble = at->query_property("prepared");
  if(wibble>5) wibble = 6;
  else wibble = wibble +1;
  if(!wibble) wibble = 1;
  at->set_property("prepared", wibble );
  remove();
  return;
}

void int_skill(object *arg) {
  if(sizeof(arg) != 2 && !objectp(arg[0])) {
    remove();
    return;
  }
  message("my_action", "%^CYAN%^You disrupted your preparation efforts.",arg[0]);
  message("other_action", (string)arg[0]->query_cap_name() +
    " disrupts "+(string)arg[0]->query_possessive()+
    "preparation efforts.",
	  all_inventory(arg[1]),
	  ({ arg[0] }) );
  remove();
  return;
}
