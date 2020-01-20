inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","curse");
    set_property("skill","necromancy");
    set_property("casting time",5);
    set_property("base mp cost",35);
    set_property("dev cost", 27);
    set_property("fast dev cost", 65);
    set_property("spell level", 5);
    set_property("moon","ankh");
    set_property("caster message","You cast a curse on $T.");
    set_property("target message","$C casts a curse on you.");
    set_property("observer message","$C casts a curse on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "-2D6");
    set_property("stats", ({ "strength", "intelligence", "dexterity" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("combat spell", 1);
    set_property("duration", 240);
    set_property("stack key", "hex");
    set_property("stack num", 3);
    set_property("prereq", "hex");
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell gives a general short-term penalty in skills and stats to the "
"target.  Curses are stackable.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if((int)at->query_curse_num() >= 3) {
    message("info", (string)at->query_cap_name() +
	    " already has the maximum number of curse spells on "+
	    objective(at) + ".", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/curse_shadow");
  ob->set_curse(power * -(random(5) + 1));
  ob->start_shadow(at, props["duration"],
		   "%^CYAN%^A curse spell wears off.");
  ::spell_func(caster, at, power, args, flag);
  return;
}

