inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","resurrect");
    set_property("skill","prayer");
    set_property("casting time",32);
    set_property("base mp cost",110);
    set_property("dev cost", 70);
    set_property("fast dev cost", 195);
    set_property("spell level", 12);
    set_property("moon","ankh");
    set_property("caster message","You cast a resurrection spell at $T.");
    set_property("target message","$C casts a resurrection spell at you.");
    set_property("observer message","$C casts a ressurection spell at $T.");
    set_property("spell type",({ }));
    set_property("target type", "player");
    set_property("must be present",1);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell revives a player from death and greatly reduces the penalties "
"incurred.  Keep in mind that the same penalties are still incurred if the "
"player does not have a corpse to which to be resurrected.  It is more difficult "
"to resurrect players of higher level than yourself, and may require casting "
"at a higher power level.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int lvl_diff;

  if(flag) {
    message("my_action", "The powers of death are accidentally turned "+
	    "against you!!!", caster);
    message("other_action", (string)caster->query_cap_name() + 
	    " accidently turns the powers of death on "+
	    objective(caster) + "self!", environment(caster),
	    ({ caster }) );
    caster->add_hp(-1 * ((int)caster->query_hp() - 1));
    remove();
    return;
  }
  lvl_diff = (int)at->query_level() - (int)caster->query_level() + 4;
  if((lvl_diff / 10) >= power) {
    message("my_action", "The spell is not powerful enough to resurrect that "+
	    "player.", caster);
    message("other_action", (string)caster->query_cap_name() + "'s "+
	    "spell was insufficient to resurrect "+
	    (string)at->query_cap_name() + ".", environment(caster),
	    ({ caster, at }) );
    message("other_action", (string)caster->query_cap_name() + "'s "+
            "spell was insufficient to resurrect you.", at);
    remove();
    return;
  }
  at->revive();
  caster->add_exp((int)at->query_level()*4000);
  remove();
  return;
}

