inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","fire shield");
    set_property("skill","magery");
    set_property("casting time",11);
    set_property("base mp cost",22);
    set_property("dev cost", 41);
    set_property("fast dev cost", 98);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You cast fire shield at $T.");
    set_property("target message","$C casts fire shield at you.");
    set_property("observer message","$C casts fire shield at $T.");
    set_property("spell type",({ "protection" }));
    set_property("protection types", ([ "fire" : 15 ]));
    set_property("duration", 120);
    set_property("target type", "living");
set_property("must be present",1);
    return;
}

void info() {
message("help",
"This spell summons a fiery shield about the target.  In addition to "
"protecting the target from fire damage, it has a chance of doing a "
"fire critical to the attacker each time he/she is hit.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "%^RED%^%^BOLD%^OOPS!  You misdirect the energies of your spell, "
            "shooting flames at the target!", caster);
    message("info", (string)caster->query_cap_name()+" accidentally shoots flames at "+
          (string)at->query_cap_name()+"!", environment(caster),
        ({ caster, at }));
    message("info", (string)caster->query_cap_name()+" accidentally shoots flames at "+
          "you!", at);
    do_critical(caster, at, ({ "fire D" }) );
    remove();
    return;
  }
  if(at->query_fire_shield()) {
    message("info", "There may only be one fire shield on a target.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/fire_shadow");
  ob->set_level(power);
  ob->start_shadow(at, props["duration"], 0);
  ::spell_func(caster, at, power, args, flag);
  remove();
  return;
}
