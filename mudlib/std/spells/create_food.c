#include "/adm/include/move.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","create food");
    set_property("skill","prayer");
    set_property("casting time",15);
      set_property("base mp cost",14);
    set_property("dev cost", 14);
    set_property("fast dev cost", 39);
    set_property("spell level", 4);
    set_property("moon","luna");
    set_property("caster message","You cast create food");
    set_property("target message","");
    set_property("observer message","$C casts create food.");
    set_property("spell type",({  }));
    set_property("prereq", "satisfy hunger");
    set_property("no target",1);
    return;
}

void info() {
message("help",
"This spell summons some food which can satisfy hunger and help to heal "
"more quickly.  The higher the power, the more satisfying the food.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "You misdirect the energies of your spell, mildly "+
	    "poisoning yourself.", caster);
    message("info", (string)caster->query_cap_name() +
	    " looks a little green.", environment(caster), ({ caster }));
    caster->add_poisoning(45);
  }
  ob = new("/std/food");
  ob->set_long("This is an item of magically created food.");
  switch(power + random(4)) {
  case 0..2:
  default:
    ob->set_name("cracker");
    ob->set_id(({ "cracker", "food" }) );
    ob->set_weight(3);
    ob->set_float_value(0.04);
    ob->set_strength(6);
    ob->set_short("A cracker");
    break;
  case 3..4:
    ob->set_name("bread");
    ob->set_id(({ "loaf", "bread", "loaf of bread", "food" }));
    ob->set_weight(10);
    ob->set_float_value(0.35);
    ob->set_strength(13);
    ob->set_short("A loaf of bread");
    break;
  case 5..6:
    ob->set_name("fish");
    ob->set_id(({ "fish", "food", "large fish" }));
    ob->set_weight(23);
    ob->set_float_value(15.0);
    ob->set_strength(18);
    ob->set_short("A large fish");
    break;
  case 7..8:
    ob->set_name("pork");
    ob->set_id(({ "pork", "food", "salt pork" }));
    ob->set_weight(20);
    ob->set_float_value(24.0);
    ob->set_strength(23);
    ob->set_short("A piece of salt pork");
    break;
  case 9..100:
    ob->set_name("steak");
    ob->set_id(({ "food", "steak", "dragon steak" }));
    ob->set_weight(35);
    ob->set_float_value(42.0);
    ob->set_strength(30);
    ob->set_short("A dragon steak");
    break;
  }
  message("my_action", "%^CYAN%^You create "+(string)ob->query_short()+".",
	  caster);
  message("other_action", "%^CYAN%^%^BOLD%^" + (string)caster->query_cap_name()+
	  " creates "+(string)ob->query_short()+".",environment(caster),
	  ({ caster }) );
  if((int)ob->move(caster) != MOVE_OK) {
    ob->move(environment(caster));
    message("info", "The food is too heavy for you.", caster);
  }
  remove();
  return;
}

