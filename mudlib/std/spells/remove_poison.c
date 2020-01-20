inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","remove poison");
    set_property("skill","body alteration");
    set_property("casting time",1);
    set_property("base mp cost",17);
    set_property("dev cost", 16);
    set_property("fast dev cost", 40);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message",
		 "You cast remove poison at $T.");
    set_property("target message","$C casts remove poison at you.");
    set_property("observer message",
		 "$C casts remove poison at $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell will help cure a player of poisoning.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  if(flag) {
    message("info", "You end up accidentally poisoning "+
	    (string)at->query_cap_name()+
	    "!", caster);
    message("info", (string)caster->query_cap_name() + 
	    " accidentally poisons you!", at);
    at->add_poisoning(20 *power*power);
    remove();
    return;
  }
  at->add_poisoning(-30*power*power);
  remove();
  return;
}

