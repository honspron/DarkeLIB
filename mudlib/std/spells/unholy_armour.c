inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","unholy armour");
    set_property("stack key", "unholy armour");
    set_property("stack num", 1);
    set_property("skill","necromancy");
    set_property("casting time",10);
   set_property("base mp cost", 100);
    set_property("dev cost", 89);
    set_property("fast dev cost", 280);
    set_property("spell level", 17);
    set_property("moon","luna");
    set_property("caster message","You cast unholy armour at $T.");
    set_property("target message","$C casts unholy armour at you.");
    set_property("observer message","$C casts unholy armour at $T.");
    set_property("spell type",({ "protection" }));
    set_property("protection types",
        ([ "cutting" : 2000, "impaling" : 2000, "crushing" : 2000,
            "impact" : 2000 ]));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("prereq", "freeze skin");
    set_property("duration", "see below");
    return;
}

void info() {
message("help",
"Welcome to the most powerful physical damage protection spell on the mud.  "
"It imbues the target with protection from ALL PHYSICAL DAMAGE (cutting, impact, etc.) "
"for a short time.  The cost of casting the spell is 296 mp per level PLUS "
"20 hit points per round that you want the spell to last!  The duration is "
"then multiplied by the power level.  Your hp is paid, not the target's.\n"
"Example: cast *3 unholy armour at diewarzau with 15\n"
"This would cost 300 mp and 300 hp and last 45 (15 x 3) rounds.\n"
"NOTE: You CAN kill yourself with this spell.  The hit points are "
"NOT paid unless the spell succeeds.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int rounds;

  if(!sscanf(args, "%d", rounds)) {
    message("info", "See 'help spell unholy armour' for syntax.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  caster->add_hp(-20 * rounds);
  props["duration"] = rounds * 2 * power;
  if(flag) {
    message("info", "%^RED%^You pay the hit points, but the spell doesn't "+
        "go off!%^RESET%^", caster);
    remove();
    return;
  }
  ::spell_func(caster, at, 1, 0, 0);
  remove();
  return;
}

