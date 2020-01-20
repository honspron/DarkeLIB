inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","battle aura");
    set_property("skill","worship of k'thach");
    set_property("casting time",17);
    set_property("base mp cost",47);
    set_property("dev cost", 66);
    set_property("fast dev cost", 181);
    set_property("spell level", 11);
    set_property("moon","ankh");
    set_property("caster message","You cast battle aura at $T.");
    set_property("target message","$C casts battle aura at you.");
    set_property("observer message","$C casts battle aura at $T.");
    set_property("spell type",({ "protection" }));
    set_property("protection types", ([ "crushing":8,
       "cutting":8, "impaling":8, "impact":8 ]));
    set_property("duration", 120);
    set_property("target type", "living");
   set_property("must be present",1);
    return;
}

void info() {
message("help",
"This spell summons a holy shield about the target.  In addition to "
"protecting the target from physical damage, it has a chance of doing an "
"impact critical to the attacker each time he/she is hit.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "%^RED%^%^BOLD%^OOPS!  You misdirect the energies of your spell, "
            "shooting flames at the target!", caster);
    message("info", (string)caster->query_cap_name()+" accidentally calls divine wrath upon "+
          (string)at->query_cap_name()+"!", environment(caster),
        ({ caster, at }));
    message("info", (string)caster->query_cap_name()+" accidentally calls divine wrath upon "+
          "you!", at);
    do_critical(caster, at, ({ "impact D" }) );
    remove();
    return;
  }
  if(at->query_battle_aura()) {
    message("info", "There may only be one battle aura on a target.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/battle_shadow");
   ob->set_power(power);
  ob->start_shadow(at, props["duration"], 0);
  ::spell_func(caster, at, power, args, flag);
  remove();
  return;
}
