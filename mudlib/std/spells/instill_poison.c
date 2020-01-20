inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","instill poison");
    set_property("skill","body alteration");
    set_property("casting time",6);
    set_property("base mp cost",17);
    set_property("dev cost", 17);
    set_property("fast dev cost", 55);
    set_property("spell level", 3);
    set_property("moon","warzau");
    set_property("caster message",
		 "You cast instill poison at $T.");
    set_property("target message","$C casts instill poison at you!");
    set_property("observer message",
		 "$C casts instill poison at $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("can resist", 1);
    set_property("save mod", "constitution");
    return;
}

void info() {
message("help",
"This is an offensive spell which poisons the target, causing it to "
"take damage.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  if(flag) {
    message("info", "You end up accidentally curing "+
	    (string)at->query_cap_name()+
	    "!", caster);
    message("info", (string)caster->query_cap_name() + 
	    " accidentally cures you of poison!", at);
    at->add_poisoning(-50 *power);
    remove();
    return;
  }
  at->add_poisoning(100*power);
  remove();
  return;
}

