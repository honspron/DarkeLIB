#include <spell.h>
#include <daemons.h>

inherit "/std/spells/spell";

int pow;

void create() {
    ::create();
    set_property("name","vengeance of k'thach");
    set_property("skill","worship of k'thach");
    set_property("casting time",28);
    set_property("base mp cost",104);
    set_property("dev cost", 110);
    set_property("fast dev cost", 350);
    set_property("spell level", 21);
    set_property("moon","luna");
    set_property("caster message","You call upon the protection of K'thach.");
    set_property("target message","");
    set_property("observer message","$C calls upon the presence of K'thach.");
    set_property("spell type",({ }));
    set_property("duration", 240);
    set_property("no target", 1);
    set_property("prereq", "retribution of k'thach");
    return;
}

void info() {
message("help",
"This is a VERY powerful spell, often allowing a war-priest to escape death.  "
"If a war priest is defeated in combat, ie, deprived of all his/her hp, K'thach "
"will exact his vengeance, taking 100-200 hp per power level from the attacker and "
"giving it to the caster.  If this is not enough to save the caster from death, "
"he/she will still die.  This spell is capable of killing the "
"opponent.  If 100-200 hp per power level is GREATER than the "
"amount of hp that the attacker has, only the attckers total hp will "
"be granted.  This spell has a small chance (0-3%) of killing the "
"attacker outright upon the death of the caster.  "
"This spell may not be stacked with other death-save spells.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
//  object ob;

  if(flag) {
    message("info", "Hmm...the spell seems to have worked...", caster);
    message("info", "Everything seems fine...BUT WAIT...you are DEAD!", at);
    caster->add_hp(-1*(int)caster->query_hp() + -10);
    remove();
    return;
  }
  if(caster->query("death save")) {
    message("info", "You cannot cast that spell now.",
       caster);
    message("info", "%^CYAN%^"+(string)caster->query_cap_name() +
          "'s spell fails.", environment(caster), ({ caster }) );
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  message("info", "K'thach now watches over you.",
        caster);
  caster->set("death save", (: call_other, this_object(), "save_from_death" :));
  pow = power;
  delayed_call("expire_me", props["duration"], caster);
  return;
}

void expire_me(object me) {
  if(!me) {
    remove();
    return;
  }
  message("info", "%^CYAN%^Vengeance of K'thach wears off.", me);
  me->set("death save", 0);
  remove();
  return;
}

void save_from_death(object caster, object at) {
  int amt = 100;
  int i;
  
  if(!caster) {
    remove_delayed_call("expire_me");
    remove();
    return;
  }
  if(!at) {
    message("info", "K'thach cannot find your attacker, and he "
      "is unable to exact vengeance!", caster);
    caster->set("death save", 0);
    remove_delayed_call("expire_me");
    remove();
    return;
  }
  caster->remove_paralyzed();
  for(i=1;i<=5;i++) amt += 1 + random(20);
  amt *= pow;
  if((amt > ((int)at->query_hp() + 1)) ||
    (random(100) < (pow/2)))
    amt = (int)at->query_hp() + 1;
  caster->heal(amt);
  at->add_hp(-1 * amt);
  message("info", "%^CYAN%^K'thach exacts his VENGEANCE upon "
    + TQN + ", giving you "+sprintf("%d of %s hit points!",
      amt, possessive(at)), caster);
  message("info", "%^CYAN%^%^BOLD%^As you defeat "+
    CQN+", the deity K'thach exacts vengeance upon you, "
    "robbing you of "+sprintf("%d of your hp and giving them to %s!",
    amt, objective(caster)), at);
  caster->set("death save", 0);
  remove_delayed_call("expire_me");
  remove();
  return;
}

