inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","hawk eyes");
     set_property("skill","woodland lore");
    set_property("casting time",8);
    set_property("base mp cost",30);
    set_property("dev cost", 30);
    set_property("fast dev cost", 100);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You hawk eyes on $T.");
    set_property("target message","$C casts hawk eyes on you.");
    set_property("observer message","$C casts hawk eyes on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "1D10");
    set_property("stats", ({ "intelligence" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 240);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell calls upon the vision of the hawk.  When cast  "
"on a target, that target can easily perceive hidden exits, people,"
"and items that he/she would not normally see",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob;

  seteuid(getuid());
  if(at->query_awareness()) {
    message("info", (string)at->query_cap_name() +
            " is already aware.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!flag) {
    ob = new("/std/spells/shadows/aware_shad");
    ob->set_power(power);
    ob->start_shadow(at, props["duration"], "%^YELLOW%^Hawk eyes wears off.");
  }
  ::spell_func(caster, at, power, args, flag);
  return;
}
