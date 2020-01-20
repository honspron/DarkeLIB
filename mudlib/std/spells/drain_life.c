inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","drain life");
    set_property("skill","necromancy");
    set_property("casting time",1);
    set_property("base mp cost",20);
    set_property("dev cost", 9);
    set_property("fast dev cost", 22);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("caster message","You cast a drain life $T.");
    set_property("target message","$C casts drain life at you!");
    set_property("observer message","$C casts drain life at $T.");
    set_property("spell type",({ }));
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell robs life of the target and gives it to the caster!  "
"The caster's max hit points may be exceeded by this spell.",
this_player());
}

int can_exceed_max_hp() { return 1; }

void spell_func(object caster, object at, int power, string args, int flag) {
  int mult, roll;

  mult = power;
//  if(at()->query_ghost()) {
//    message("info", "You can't drain the life of a ghost!", caster);
//   return;
//  }
  if(flag) {
    message("info", "You accidentally drain your own life, giving it to "
       "the target!!!", caster);
    mult *= -1;
  }
  roll = random(6) + random(6) + random(6) + 3;
  at->add_hp(-1 * mult * roll);
  caster->add_hp(mult * roll/2);
  remove();
  return;
}
