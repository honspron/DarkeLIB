inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","counter spell");
    set_property("skill","sorcery");
    set_property("casting time",0);
    set_property("base mp cost",41);
    set_property("dev cost", 98);
    set_property("fast dev cost", 280);
    set_property("spell level",15);
    set_property("moon","luna");
    set_property("caster message","You cast a counterspell at $T.");
    set_property("target message","$C casts a counterspell at you.");
    set_property("observer message","$C casts a counterspell at $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
//    set_property("can resist", 2);
//    set_property("save mod", "intelligence");
    set_property("duration", "instantaneous");
    set_property("prereq", "dispel magic");
    return;
}

void info() {
message("help",
"This is a very powerful spell which may be used to interrupt a "
"spell before it is cast.  If someone begins casting a spell, "
"you may interrupt it by casting counter spell at them before "
"their spell goes off.  Higher level spells are harder to counter, "
"but casting counter spell at a higher power helps offset this "
"penalty.  The caster's level will also increase the chance of a "
"successful counter",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  int lev;
  string *tmp;

  ob = (object)at->query_casting();
  if(!ob) {
    message("info", (string)at->query_cap_name() +
            " is not casting a spell.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You accidentally create a mana vortex in your "+
            "vicinity, draining your magic points!", caster);
    message("info", (string)caster->query_cap_name() +
            " looks a little pale.", environment(caster),
            ({ caster }));
    caster->add_mp((int)caster->query_mp() / -2);
    remove();
    return;
  }
  tmp = (string *)ob->query_property("no counter");
  if(tmp && member_array((string)caster->query_name(), tmp) >= 0) {
    message("info", "%^CYAN%^%^BOLD%^You have already attempted to counter that spell.",
            caster);
    message("info", "%^CYAN%^%^BOLD%^"+
            (string)caster->query_cap_name() +
            "'s spell fails.", environment(caster),
            ({ caster }));
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  lev = (int)ob->query_property("spell level") - caster->query_level() + 6;
  if(lev < 0 && !resist_flag) {
    message("info", "%^CYAN%^You successfully counter "+
            (string)at->query_cap_name() + "'s spell!", caster);
    message("info", "%^RED%^%^BOLD%^"+
            (string)caster->query_cap_name() +
            " counters your spell!", at);
    ob->remove();
    remove();
    return;
  }
  if(random(20) > (lev+2-power) && !resist_flag) {
    message("info", "%^CYAN%^You successfully counter "+
            (string)at->query_cap_name() + "'s spell!", caster);
    message("info", "%^RED%^%^BOLD%^"+
            (string)caster->query_cap_name() +
            " counters your spell!", at);
    ob->remove();
    remove();
    return;
  } else {
    message("info", "%^CYAN%^Your counterspell fails.", caster);
    message("info", "%^CYAN%^%^BOLD%^"+
            (string)caster->query_cap_name() +
            " tried unsuccessfully to counter your spell.",
            at);
    if(tmp)
      ob->set_property("no counter", tmp +
                       ({ (string)caster->query_name() }) );
    else
      ob->set_property("no counter",
                       ({ (string)caster->query_name() }) );
    remove();
    return;
  }
  remove();
  return;
}
