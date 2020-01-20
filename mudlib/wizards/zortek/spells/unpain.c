inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","unpain");
    set_property("skill","mentalism");
    set_property("casting time",1);
    set_property("base mp cost",15);
    set_property("dev cost", 10);
    set_property("fast dev cost", 30);
    set_property("spell level", 1);
    set_property("moon","ankh");
    set_property("caster message","You focus unpain upon $T.");
    set_property("target message","$C focuses a gaze upon you and you feel better!");
    set_property("observer message","$C focuses a gaze upon $T.");
    set_property("spell type",({ }));
    set_property("must be present", 1);
    set_property("target type", "living");
    set_property("can overcast", 1);
    return;
}

void info() {
write(@HELP
This focus allows the mentalist to lessen the pain of a target.
It is possible for the target to exceed his or her maximum number
of hit points; however, there is a possibility of a raging insanity,
loss of stats, or instant death extreme cases caused by disruption
to the central nervous system of the target.
HELP
);
}

int can_exceed_max_hp() { return 1; }

void spell_func(object caster, object at, int power, string args, int flag) {
  int x, mult, roll, hp, max_hp;

  mult = 1;
  if(flag) {
    switch ( random(3) ) {
      case 0 : 
        message("info", "%^BOLD%^RED%^You cause pain to "+at->query_cap_name()+"!!!%^RESET%^", caster);
        message("info", "%^BOLD%^RED%^"+caster->query_cap_name()+" seems to be screaming in your mind!!!%^RESET%^", at);
        mult = -1;
        break;
      case 1 :
        message("info", "%^BOLD%^RED%^You cause %^WHITE%^GREAT%^RED%^ pain to "+at->query_cap_name()+"!!!%^RESET%^", caster);
        message("info", "%^BOLD%^RED%^Images of "+caster->query_cap_name()+" torturing you flash in your mind!!!%^RESET%^", at);
        mult = -2;
        break;
      case 2 :
        message("info", "%^BOLD%^RED%^You cause %^WHITE%^MASSIVE%^RED%^ pain to "+at->query_cap_name()+"!!!%^RESET%^", caster);
        message("info", "%^BOLD%^RED%^Images of "+caster->query_cap_name()+" eating your brain flash in your mind!!!%^RESET%^", at);
        mult = -3;
        break;
    }
  }
  roll = 1;
  for(x=0;x<6*power;x++) {
    roll += (random(4) + 1)*mult;
  }
  at->add_hp(roll);
  caster->add_mp(roll/-2);
  if( (int)caster->query_mp() < (-1 * ((int)caster->query_max_mp()/10))) {
    message("info", @TEXT
The power of your focus is such that you have forgotten the limits
of your skill and ability.  You pour every shred of your essence into
the link leaving nothing to sustain your physical host body.
TEXT
, caster);
    caster->die();
  }
  hp = (int)at->query_hp();
  max_hp = (int)at->query_max_hp();
  if( (hp-roll) > max_hp ) {
    if(hp > max_hp * 3) {
      message("info", @TEXT
You suddenly feel completely numb all over....extreme sleepiness
washes over you.  Seeing the stoney gaze from  a stranger's face
is the last image your eyes discern.
TEXT
, at);
      at->set_hp(-1);
      caster->add_exp( (int)at->query_exp()/100 );
    }
    else {
      if( ( (hp/(max_hp*3+max_hp*3))*100 > random(100) + 17) ) {
        switch(random(3)+1) {
          case 1:
            if(at != caster) {
              message("info", "You suddenly fly into a insane rage!", at);
              at->kill_ob(caster);
            }
            else {
              message("info", "You briefly fall into a raging depression!");
              at->do_damage("head", (random(2)+1)*power);
            }
            break;
          case 2:
            message("info", "You feel slightly dizzy and light headed.");
            at->set_stats("intelligence", (int)at->query_stats("intelligence")-1);
            break;
          case 3:
            message("info", "You feel slightly dizzy and light headed.");
            at->set_stats("wisdom", (int)at->query_stats("constitution")-1);
            break;
          default:
            message("info", "You briefly fall into a fit of depression!");
            at->do_damage("head", power);
        }
      }
    }  
  }
  remove();
  return;
}
