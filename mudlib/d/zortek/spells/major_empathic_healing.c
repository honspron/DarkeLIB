inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","major empathic healing");
    set_property("skill","mentalism");
    set_property("casting time",5);
    set_property("base mp cost",6);
    set_property("dev cost", 14);
    set_property("fast dev cost", 42);
    set_property("spell level", 5);
    set_property("moon","ankh");
    set_property("caster message","You begin to feel $T's pain.");
    set_property("target message","$C peers at you and you feel better!");
    set_property("observer message","$C peers at $T.");
    set_property("spell type",({ }));
    set_property("must be present", 1);
    set_property("target type", "living");
    set_property("can overcast", 1);
    return;
}

void info() {
write(@HELP
This focus allows the caster to transfer the burdon of wounds from
a subject unto hirself.  In addition to the inital concentration
cost, the empath must pay addtional mental points based upon the
amount of damage transfered.  (RESTATED) The damage is not simply
healed, but is TRANSFERED to the caster FROM the target.  There are
cases where this focused discipline has been know to fail and work
in reverse!
HELP
);
}

int can_exceed_max_hp() { return 0; }

void spell_func(object caster, object at, int power, string args, int flag) {
  int x, mult, roll, hp, max_hp;

  mult = power;
  if(flag) {
    message("info","%^RED%^BOLD%^You have a gross loss of focus and cause "+
            at->query_cap_name()+" to experience %^WHITE$%MAJOR%^RED%^ pain!!!%^RESET%^", caster);
    message("info","%^RED%^BOLD%^"+caster->query_cap_name()+
            "loses all concentration and floods you with a %^WHITE$%MAJOR%^RED%^ amount of pain!!!%^RESET%^", at);
    mult *= -2;
  }
  roll = 1;
  for(x=0;x<4*power;x++) {
    roll += random(5)+1;
  }
// Min/Max 4/20  Level 1
  at->add_hp(roll);
  caster->add_mp(-1 * roll/3);
  caster->do_damage("torso", roll);
  message("info","You feel pain as wounds appear on your torso.", caster);

  if( (int)caster->query_mp() <
      -1 * ((int)caster->query_max_mp()/(10))) {
    message("info", @TEXT
The power of your focus is such that you have over estimated the limits
of your skill and ability.  You push far too much of your essence into
the link causing your physical body to suffer in excess of the pain you
have tried to transfer.  As a result, you suddenly feel like something
just branded your brain with a white-hot iron.
TEXT
, caster);
    caster->do_damage("head", roll/3);
  }
  remove();
  return;
}
