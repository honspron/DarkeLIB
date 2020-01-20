inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","levitation");
    set_property("skill","magery");
    set_property("casting time",7);
    set_property("base mp cost",20);
    set_property("dev cost", 14);
    set_property("fast dev cost", 45);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","You begin to levitate above the ground.");
    set_property("target message","");
    set_property("observer message","$C begins to levitate above the ground.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 40);
    return;
}

void info() {
message("help",
"This spell allows the player to levitate slightly above the gound.  This "
"allows crossing of hazardous terrain or water easily.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  if(caster->query_flying()) {
    message("info", "You are already flying!", caster);
    message("info", (string)caster->query_cap_name()+"'s spell fails.",
	    environment(caster), ({ caster }) );
    remove();
    return;
  }
  ob = new("/std/spells/shadows/lev_shadow");
  ob->start_shadow(caster, props["duration"],
	           "You cease to levitate.");
  return;
}
