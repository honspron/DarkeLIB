inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","holy aura");
    set_property("skill","prayer");
    set_property("casting time",11);
    set_property("base mp cost",41);
    set_property("dev cost", 53);
    set_property("fast dev cost", 127);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You cast holy aura at $T.");
    set_property("target message","$C casts holy aura at you.");
    set_property("observer message","$C casts holy aura at $T.");
    set_property("spell type",({ "protection" }));
    set_property("protection types", ([ "crushing" : 7,
        "cutting" : 5, "impaling" : 5, "impact" : 7, "disruption": 15 ]));
    set_property("duration", 120);
    set_property("target type", "living");
   set_property("must be present",1);
    set_property("prereq", "holy armour");
    return;
}

void info() {
message("help",
"This spell summons a holy shield about the target.  In addition to "
"protecting the target from disruption damage, it has a chance of doing a "
"holy critical to the attacker each time he/she is hit.  It also offers some"
"minimal protection against physical damage",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "%^RED%^%^BOLD%^OOPS!  You misdirect the energies of your spell, "
            "calling divine wrath at the target!", caster);
    message("info", (string)caster->query_cap_name()+" accidentally calls divine wrath upon "+
          (string)at->query_cap_name()+"!", environment(caster),
        ({ caster, at }));
    message("info", (string)caster->query_cap_name()+" accidentally calls divine wrath upon "+
          "you!", at);
    do_critical(caster, at, ({ "holy C" }) );
    remove();
    return;
  }
  if(at->query_holy_aura()) {
    message("info", "There may only be one holy aura on a target.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/holy_shadow");
ob->set_power(power);
  ob->start_shadow(at, props["duration"], 0);
  ::spell_func(caster, at, power, args, flag);
  remove();
  return;
}
