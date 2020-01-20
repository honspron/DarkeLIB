#include <spell.h>
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon");
    set_property("skill","magery");
    set_property("casting time",12);
    set_property("base mp cost",45);
    set_property("dev cost", 55);
    set_property("fast dev cost", 140);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast a summoning spell.");
    set_property("target message","");
    set_property("observer message","$C utters some magical incantations.");
    set_property("target observer message", "A magical aura enshrouds $T.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("prereq", "scry");
    return;
}

void info() {
message("help",
"This spell summons a player from anywhere on the mud to your location.  "
"This summoning need not be voluntary, but you will have trouble "
"summoning higher level players if you cast this spell at low power.  "
"You must scry the target before casting this spell, and therefore, a "
"target need not be supplied.\n"
"Example: cast *3 summon",
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
    message("info", "%^RED%^%^BOLD%^You accidentally summon a creature from the warp!",
          caster);
    message("info", "%^RED%^%^BOLD%^A hideous creature is gated from the warp!",
          environment(caster), ({ caster }) );
    seteuid(getuid());
    new("/wizards/diewarzau/obj/mon/warp_creature")->move(environment(caster));
    remove();
    return;
  }
  if(wizardp(at)) {
    message("info", "You may not summon wizards.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(at->is_player() && !interactive(at)) {
    message("info", "You may not summon link-dead players.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(environment(at)->query_property("no summon")) {
    message("info", "You may not summon anyone from "+
            (string)at->query_cap_name()+"'s location.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(environment(caster)->query_property("no teleport")) {
     message("info", "You may not summon anyone to your location.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  diff = (int)at->query_level() - (int)caster->query_level();
  diff += 23 - (power * 4);
  if(random(20) <= diff) {
    message("info", "Your summoning spell was insufficient to summon "+
            (string)at->query_cap_name()+".", caster);
    message("info", (string)caster->query_cap_name() +
            " tried unsuccessfully to summon you.", at);
    remove();
    return;
  }
  message("info", "%^GREEN%^%^BOLD%^You are magically transported to "+
          (string)caster->query_cap_name() + ".", at);
  at->move_player(environment(caster), 0);
  remove();
  return;
}
