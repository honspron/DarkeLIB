inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","test");
     set_property("skill","magery");
    set_property("casting time",8);
    set_property("base mp cost",30);
    set_property("dev cost", 30);
    set_property("fast dev cost", 100);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You cast awareness on $T.");
    set_property("target message","$C casts awareness on you.");
    set_property("observer message","$C casts awareness on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "1D10");
    set_property("stats", ({ "intelligence" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 10);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell was created by an unknown arch-mage.  When cast  "
"on a target, that target can easily perceive hidden exits, people,"
"and items that he/she would not normally see",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
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
    ob = new("/std/spells/shadows/war_test");
    ob->set_power(power);
    ob->start_shadow(caster, props["duration"],
                   "%^RED%^Awareness wears off.");
  }
  ::spell_func(caster, at, power, args, flag);
  return;
}
