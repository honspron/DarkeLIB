inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","intoxication");
    set_property("skill","body alteration");
    set_property("casting time",12);
    set_property("base mp cost",30);
    set_property("dev cost", 12);
    set_property("fast dev cost", 30);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message",
		 "You cast intoxication at $T....*hiccup*.");
    set_property("target message","$C casts a spell, and you feel drunk.");
    set_property("observer message",
		 "$C casts intoxication at $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("prereq", "satisfy thirst");
    return;
}

void info() {
message("help",
"This is a rather amusing spell.  It instills the spirit of alcohol into "
"a \"victim's\" blood stream, causing him/her to become drunk.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  if(flag) {
    message("info", "You accidentally poison "+(string)at->query_cap_name()+
	    "!", caster);
    message("info", (string)caster->query_cap_name() + 
	    " accidentally poisons you!", at);
    at->add_poisoning(10*power);
    remove();
    return;
  }
  if(!at->add_intox((17 + random(10)) * power))
     message("info", (string)at->query_cap_name()+ " is too drunk.",
	     caster);
  remove();
  return;
}

