inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental presence");
    set_property("skill","elementalism");
    set_property("elemental spell", 1);
    set_property("casting time",11);
    set_property("base mp cost",30);
    set_property("dev cost", 41);
    set_property("fast dev cost", 98);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You cast elemental presence at $T.");
    set_property("target message","$C casts elemental presence at you.");
    set_property("observer message","$C casts elemental presence at $T.");
    set_property("spell type",({ "protection" }));
    set_property("ele protection", 25);
    set_property("duration", 120);
    set_property("target type", "living");
set_property("must be present",1);
    set_property("prereq", "body of elements");
    return;
}

void info() {
message("help",
"This spell serves two functions.  First, it affords the caster a good deal "
"of protection from the element cast.  In addition, if the caster is hit in "
"combat, there is a chance that the attacker will receive an elemental "
"critical in return!",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "%^RED%^%^BOLD%^OOPS!  You misdirect the energies of your spell, "
            "shooting elemental bolts at the target!", caster);
    message("info", (string)caster->query_cap_name()+" accidentally shoots elemental bolts at "+
          (string)at->query_cap_name()+"!", environment(caster),
        ({ caster, at }));
    message("info", (string)caster->query_cap_name()+" accidentally shoots elemental bolts at "+
          "you!", at);
    do_critical(caster, at, map_array(props["element types"], (: $1 + $2 :),
				      " C"));
    remove();
    return;
  }
  if(at->query_ele_pres()) {
    message("info", "There may only be one fire elemental presence on a target.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/ele_pres_shad");
ob->set_power(power);
  ob->set_damage(props["element types"]);
  ob->start_shadow(at, props["duration"], 0);
  ::spell_func(caster, at, power, args, flag);
  remove();
  return;
}
