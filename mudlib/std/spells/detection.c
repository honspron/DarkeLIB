inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","detection");
    set_property("skill","woodland lore");
    set_property("casting time",12);
    set_property("base mp cost",45);
    set_property("dev cost", 62);
    set_property("fast dev cost", 180);
    set_property("spell level",15);
    set_property("moon","luna");
    set_property("caster message","You cast detection on $T.");
    set_property("target message","$C casts detection on you");
    set_property("observer message","$C casts detection on $T.");
    set_property("spell type",({ }));
    set_property("duration", 180);
    set_property("target type", "living");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell allows the target to see invisible players without "
"penalty.  Power affects duration only.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob;

  if(flag) {
    message("info", "Hmm...the spell seems to have worked...", caster);
    message("info", "Everything seems fine...BUT WAIT...you are BLIND!",
at);
    ob = new("/std/spells/shadows/blind_shadow");
    ob->start_shadow(at);
    call_out("expire_blind", props["duration"], at, ob);
    return;
  }
  if(at->query("see invis")) {
    message("info", nominative(at) + " can already see invisible...your spell fails.", caster);
    message("info", ""+(string)caster->query_cap_name() +
          "'s spell fails.", environment(caster), ({ caster }) );
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  message("info", "You may now see the invisible...",
        at);
  at->set("see invis", 1);
  call_out("expire_me", props["duration"], caster);
  return;
}

void expire_blind(object me, object shad) {
  if(!me || !shad) {
    remove();
    return;
  }
  shad->external_destruct(shad);
  message("info", "You can see again.", me);
  remove();
  return;
}

void expire_me(object me) {
  if(!me) {
    remove();
    return;
  }
  message("info", "%^BOLD%^%^GREEN%^Detection wears off.", me);
  me->set("see invis", 0);
  remove();
  return;
}
