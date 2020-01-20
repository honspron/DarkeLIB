#include <spell.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","combat healing");
    set_property("skill","prayer");
    set_property("casting time",15);
    set_property("base mp cost",37);
    set_property("dev cost", 31);
    set_property("fast dev cost", 87);
    set_property("spell level", 6);
    set_property("moon","ankh");
    set_property("caster message","You cast combat healing upon $T.");
    set_property("target message","$C casts combat healing upon you.");
    set_property("observer message","$C casts combat healing upon $T.");
    set_property("spell type",({  }));
    set_property("must be present",1);
    set_property("duration", "see below");
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell is very useful in preparation for combat.  It will heal the target "
"AUTOMATICALLY during combat until the 'heal battery' of the spell "
"is exhausted.  When the target drops below a certain percent of hit points, he/she is "
"automatically healed of up to 40 hp per power level (5d8).  The spell expires "
"when the heal 'battery' is exhausted.  The battery contains 200 hp per power level.  "
"If the player receives a good deal of damage in a round, he/she may still be killed "
"if the battery is not exhausted.\n"
"Syntax: cast *3 combat healing at <target> with <percentage>\n"
"Ex: cast *3 combat healing at diewarzau with 50\nThe spell will attempt to heal "
"any time hp drops below 50% max (must be 1-75).\n"
"NOTE: This spell will heal you a MAXIMUM of one time per round.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  int perc;

  if(at->query_auto_heal()) {
    message("info", "You may only cast one spell of this type at a time "+
      "on any one target.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!args || !sscanf(args, "%d", perc)) {
    message("info", "See 'help spell combat healing' for syntax.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(perc < 1 || perc > 75) {
    message("info", "The percentage must fall between 1 and 75.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "Oops, you accidentally reduce the recipient to "+
       "1 hp!", caster);
    message("info", CQN+" accidentally harms you!", at);
    at->add_hp(-1*((int)at->query_hp()-1));
    remove();
    return;
  }
  ob = new("/std/spells/shadows/auto_heal_shad");
  ob->set_perc(perc);
  ob->set_pow(power);
  ob->start_shadow(at, 200*power, "%^CYAN%^The heal battery has expired.");
  remove();
  return;
}

