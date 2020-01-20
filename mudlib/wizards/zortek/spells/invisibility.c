inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","invisibility");
    set_property("skill","illusionism");
    set_property("casting time",13);
    set_property("base mp cost",47);
    set_property("dev cost", 65);
    set_property("fast dev cost", 170);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast invisibility at $T.");
    set_property("target message","$C casts invisibility at you.");
    set_property("observer message","$C casts invisibility at $T.");
    set_property("spell type",({ }));
    set_property("duration", 121);
    set_property("target type", "living");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell causes the target to vanish from sight!  If the target enters, "
"the spell will be cancelled.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "Hmm...the spell seems to have worked...", caster);
    message("info", "Everything seems fine...BUT WAIT...you're invisible, "+
          "but you are BLIND TOO!", at);
    ob = new("/std/spells/shadows/blind_shadow");
    ob->start_shadow(at);
    call_out("expire_blind", props["duration"], at, ob);
  }
  if(at->query_invis()) {
    message("info", nominative(at) + " is already invisible...your spell fails.",
       caster);
    message("info", "%^CYAN%^"+(string)caster->query_cap_name() +
          "'s spell fails.", environment(caster), ({ caster }) );
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  message("info", "You fade into invisibility...",
        at);
  message("info", (string)at->query_cap_name() +
        " fades from sight.",
        environment(caster), ({ caster }) );
  ob = new("/std/spells/shadows/invis_shadow");
  ob->start_shadow(at, props["duration"], "%^CYAN%^An invisibility spell wears off.");
  remove();
  return;
}
