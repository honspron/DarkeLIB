inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","winged flight");
    set_property("skill","body alteration");
    set_property("casting time",7);
    set_property("base mp cost",15);
    set_property("dev cost", 11);
    set_property("fast dev cost", 33);
    set_property("spell level", 2);
    set_property("moon","luna");
    set_property("caster message","You sprout wings.");
    set_property("target message","");
    set_property("observer message","$C sprouts wings.");
    set_property("no target", 1);
    set_property("spell type",({ }));
    set_property("duration", 180);
    return;
}

void info() {
message("help",
"This spell allows the player to fly above the gound.  This "
"allows crossing of hazardous terrain or water easily.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  if(flag) {
    remove();
    return;
  }
  at=caster;
  if(caster->query_flying()) {
    message("info", "You are already flying!", caster);
    message("info", (string)caster->query_cap_name()+"'s spell fails.",
	    environment(caster), ({ caster }) );
    remove();
    return;
  }
  ob = new("/std/spells/shadows/lev_shadow");
  ob->start_shadow(caster, props["duration"],
	           "Your wings recede into your body.");
  return;
}
