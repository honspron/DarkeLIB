inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","entangle");
    set_property("skill","woodland lore");
    set_property("casting time",2);
    set_property("base mp cost",30);
    set_property("dev cost", 24);
    set_property("fast dev cost", 70);
    set_property("spell level", 5);
    set_property("moon","warzau");
    set_property("caster message","You attempt to entangle $T.");
    set_property("target message","$C attempts to entangle you!");
    set_property("observer message","$C attempts to entangle $T.");
    set_property("must be present", 1);
    set_property("can resist", 1);
    set_property("save mod", "strength");
    set_property("damage multiplier", 6);
    set_property("combat spell", 1);
    set_property("duration", 15);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell attempts to stun the target.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  if(flag) {
    message("info", "%^BOLD%^%^RED%^OOPS, You entangle yourself!!!%^BOLD%^%^RED%^", caster);
    at = caster;
  }
  if (random(20) < (caster->query_level() - at->query_level() + 10 +
power))
    {
      at->set_paralyzed(props["duration"], "%^BOLD%^%^RED%^You are entangled and can't move%^RESET%^");
      if(!flag)
        message("info", "%^BOLD%^%^RED%^You are entangled!%^RESET%^", at);
      remove();
    }
  else
    {
      message("info", "You fight off the entanglement!", at);
      message("info", at->query_true_name()+" fights off the entanglement!", caster);
      remove();
    }
  return;
}
