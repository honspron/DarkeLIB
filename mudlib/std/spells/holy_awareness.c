inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","holy awareness");
     set_property("skill","body alteration");
    set_property("casting time",12);
    set_property("base mp cost",35);
    set_property("dev cost", 66);
    set_property("fast dev cost", 148);
    set_property("spell level", 12);
    set_property("moon","ankh");
    set_property("caster message","You cast holy awareness on $T.");
    set_property("target message","$C casts holy awareness on you.");
    set_property("observer message","$C casts holy awareness on $T.");
    set_property("spell type",({ "stat mod", "skill mod" }));
    set_property("stat dice", "1D6");
    set_property("skill dice", "4D8");
    set_property("stats", ({ "intelligence" }) );
    set_property("skills", ({ "perception" }));
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 300);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell will temporarily enhance the target's intelligence "
"and heightened his/her perception.  It also allows the target to "
"see invisible players/monsters.",

this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
//  object ob;

  seteuid(getuid());
  if(at->query_hawareness()) {
    message("info", (string)at->query_cap_name() +
            " is already aware.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!flag) {
    at->set("see invis", 1);
    call_out("expire_me", props["duration"], at);
  }
  ::spell_func(caster, at, power, args, flag);
  return;
}

void expire_me(object at) {
  message("info", "%^CYAN%^You may no longer see invisible.",
    at);
  at->set("see invis", 0);
  remove();
  return;
}

