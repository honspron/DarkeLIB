#include "/adm/include/spell.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","call divine strength");
    set_property("skill","prayer");
    set_property("casting time",12);
    set_property("base mp cost",61);
    set_property("dev cost", 39);
    set_property("fast dev cost", 100);
    set_property("spell level", 8);
    set_property("moon","ankh");
    set_property("caster message","You cast call divine strength.");
    set_property("target message","$C casts call divine strength.");
    set_property("observer message","$C casts call divine strength.");
    set_property("spell type",({  }));
    set_property("no target", 1);
    return;
}

int can_exceed_max_hp() { return 1; }

void info() {
message("help",
"This spell does not need a target, since it may only ba cast on the caster "
"him/herself, since it is so powerful.  It may also NOT be cast while "
"in combat.  It is much like a powerful heal spell, "
"except that it may ONLY be used when the caster is within 10% of his/her max "
"hp, and it allows the caster to EXCEED his/her max hp!!!  It allows the caster to "
"'charge' him/herself up for battle.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int roll, i;
  
  if(flag) {
    message("info", "Instead of charging for battle, you reduce yourself to "+
      "1 hit point! (oops)", caster);
    message("info", (string)caster->query_cap_name() +
      " doesn't look too good.", EC, ({ caster }));
    caster->add_hp(-1 * ((int)caster->query_hp() - 1));
    remove();
    return;
  }
  if((int)caster->query_hp() > (int)caster->query_max_hp()) {
    message("info", "This spell may not be cast while you are "+
      "over max hp.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if((int)caster->query_hp() < ((int)caster->query_max_hp()*9)/10) {
    message("info", "This spell must be cast while you are "+
      "within 10% or less of your max hp.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(caster->query_current_attacker()) {
    message("info", "This spell may not be cast while you are "+
      "in combat.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  caster->add_hp((int)caster->query_max_hp() -
    (int)caster->query_hp());
  roll = 0;
  for(i=1;i<10;i++) roll += random(20) + power;
  roll *= power;
  caster->set_property("allow_over_max",1);
  caster->add_hp(roll);
  caster->set_property("allow_over_max",0);
  message("info", "You have been granted "+roll+" extra hp over your max "+
    "for a total of "+(int)caster->query_hp()+"!", caster);
  remove();
  return;
}

