inherit "/std/spells/spell";

void create() {
    ::create();
   set_property("name","transport");
    set_property("skill","magery");
    set_property("casting time",21);
    set_property("base mp cost",45);
    set_property("dev cost", 62);
    set_property("fast dev cost", 135);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast transport.");
    set_property("target message","$C attampts to teleport to you.");
    set_property("observer message","$C utters some magical incantations.");
    set_property("target observer message", "A magical aura coalesces next to $T.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("prereq", "scry");
    return;
}

void info() {
message("help",
"This spell may be used to teleport to a player.  In order to "
"teleport to higher-level players, the spell must be cast at a higher "
"power level.  You need to scry the target first, and therefore you "
"need not supply a target.\n\n"
"Ex:\ncast *3 transport",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int diff;

  if(!(at = (object)caster->query("scry"))) {
    message("info", "You must scry the target first ('help spell scry').",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(time() > (int)caster->query("scry time")) {
    message("info", "Your scry has expired.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "%^RED%^%^BOLD%^ACK!  You transport yourself somewhere, "
        "but it isn't to "+(string)at->query_cap_name()+"!", caster);
    caster->move_player("/wizards/diewarzau/rooms/warp");
    remove();
    return;
  }
  if(wizardp(at)) {
    message("info", "You may not teleport to wizards.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(at->is_player() && !interactive(at)) {
    message("info", "You may not teleport to link-dead players.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(environment(at)->query_property("no teleport")) {
     message("info", "You may not teleport to that location.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  diff = (int)at->query_level() - (int)caster->query_level();
  diff += 23 - (power*4);
  if(random(20) <= diff) {
    message("info", "Your transport spell was insufficient to teleport to "+
            (string)at->query_cap_name()+".", caster);
    message("info", (string)caster->query_cap_name() +
            " tried unsuccessfully to teleport to you.", at);
    remove();
    return;
  }
  message("info", "%^GREEN%^%^BOLD%^You are magically transported to "+
          (string)at->query_cap_name() + ".", caster);
  caster->move_player(environment(at), 0);
  remove();
  return;
}

