inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","major empathic surgery");
    set_property("skill","mentalism");
    set_property("casting time",13);
    set_property("base mp cost",27);
    set_property("dev cost", 38);
    set_property("fast dev cost", 114);
    set_property("spell level", 13);
    set_property("moon","ankh");
    set_property("caster message","You begin to experience $T's vast suffering.");
    set_property("target message","$C peers at you and your vast suffering is reduced!");
    set_property("observer message","$C peers at $T.");
    set_property("spell type",({ }));
    set_property("must be present", 1);
    set_property("target type", "living");
    set_property("can overcast", 1);
    return;
}

void info() {
write(@HELP
This focus allows the caster to transfer the burdon of suffering
from a subject unto hirself.  In addition to the inital concentration
cost, the empath must pay addtional mental points based upon the
amount of damage POTENTIALLY transfered.  Surgery has the potential
of healing a lot more damage than the lower level healings; however,
more of the danger is shared by the target of this focus.
HELP
);
}

int can_exceed_max_hp() { return 0; }

void spell_func(object caster, object at, int power, string args, int flag) {
  int x, mult, roll, hp, max_hp;

  mult = power;
  if(flag) {
    message("info","%^BOLD%^RED%^You cause "+at->query_cap_name()+
    " to experience %^WHITE%^UnBeLiEvAbLy MASSIVE%^RED%^ pain!!!%^RESET%^", caster);
    message("info","%^RED%^BOLD%^"+caster->query_cap_name()+
            " floods you with a %^WHITE%^UnBeLiEvAbLy MASSIVE%^RED%^ amount of pain!!!%^RESET%^", at);
    mult *= -4;
  }
  roll = 1;
  for(x=0;x<12*power;x++) {
    roll += random(10) + 1;
  }
  at->add_hp(roll);
  caster->add_mp(-1 * roll/4);
  caster->do_damage("torso", roll/3);

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
    message("info", @TEXT
The power of the mental channel is such that you have experienced
a backlash and feel wilde images of horror race through your head.
Suddenly you feel an explosion of pain like something just branded
your brain with a white-hot iron.
TEXT
, at);
    caster->do_damage("head", roll/3);
    at->do_damage("head", roll/3);
  }
  remove();
  return;
}
