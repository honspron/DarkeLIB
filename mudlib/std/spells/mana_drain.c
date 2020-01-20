inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","mana drain");
    set_property("skill","sorcery");
    set_property("casting time",7);
    set_property("base mp cost",35);
    set_property("dev cost", 54);
    set_property("fast dev cost", 130);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You cast mana drain at $T.");
    set_property("target message","$C casts mana drain at you!");
    set_property("observer message","$C casts mana drain at $T.");
    set_property("must be present", 1);
    set_property("can resist", 1);
    set_property("save mod", "intelligence");
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell attampts to drain magic points from the target.  The casting "
"cost is not spent if the spell is successful!",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int amt;
  
  if(!flag) caster->add_mp(props["mp cost"]);
  else {
    message("info", "You accidentally rob yourself of magic points!", caster);
    at = caster;
  }
  amt = power * (13 + random(10) + random(10) + random(10));
  if(amt > (int)at->query_mp()) amt = (int)at->query_mp();
  at->add_mp(-1 * amt);
  if(!flag) caster->add_mp(amt);
  remove();
  return;
}

int can_exceed_max_mp() { return 1; }
