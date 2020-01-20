#include <spell.h>
#include <daemons.h>

inherit "/std/spells/spell";

int pow;

void create() {
    ::create();
    set_property("name","retribution of k'thach");
    set_property("skill","worship of k'thach");
    set_property("casting time",60);
    set_property("base mp cost",41);
    set_property("dev cost", 26);
    set_property("fast dev cost", 85);
    set_property("spell level", 5);
    set_property("moon","luna");
    set_property("caster message","You call upon the protection of K'thach.");
    set_property("target message","");
    set_property("observer message","$C calls upon the presence of K'thach.");
    set_property("spell type",({ }));
    set_property("duration", 120);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This is quite a powerful spell, often allowing a war-priest to escape death.  "
"If a war priest is defeated in combat, ie, deprived of all his/her hp, K'thach "
"will exact his retribution, taking 7D10 hp per power level from the attacker and "
"giving it to the caster.  If this is not enough to save the caster from death, "
"he/she will still die.  Also, this spell will never kill the opponent, merely "
"reduce the attackers hp to 1.  If 7D10 per power level is GREATER than the "
"amount of hp that the attacker has, only the attckers total hp (minus 1) will "
"be granted.  This spell may not be stacked with other death-save spells.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
//  object ob;

  if(flag) {
    message("info", "Hmm...the spell seems to have worked...", caster);
    message("info", "Everything seems fine...BUT WAIT...you have lost half your hp!", caster);
    caster->add_hp(-1*(int)caster->query_hp() / 2);
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
  message("info", "%^CYAN%^Retribution of K'thach wears off.", me);
  me->set("death save", 0);
  remove();
  return;
}

void save_from_death(object caster, object at) {
  int amt = 0;
  int i;
  
  if(!caster) {
    remove_delayed_call("expire_me");
    remove();
    return;
  }
  if(!at) {
    message("info", "K'thach cannot find your attacker, and he "
      "is unable to exact retribution!", caster);
    remove_delayed_call("expire_me");
    caster->set("death save", 0);
    remove();
    return;
  }
  caster->remove_paralyzed();
  for(i=1;i<=7;i++) amt += 1 + random(10);
  amt *= pow;
  if(amt > ((int)at->query_hp() - 1))
    amt = (int)at->query_hp() - 1;
  caster->heal(amt);
  at->add_hp(-1 * amt);
  message("info", "%^CYAN%^K'thach exacts his revenge upon "
    + TQN + ", giving you "+sprintf("%d of %s hit points!",
      amt, possessive(at)), caster);
  message("info", "%^CYAN%^%^BOLD%^As you defeat "+
    CQN+", the deity K'thach exacts retribution upon you, "
    "robbing you of "+sprintf("%d of your hp and giving them to %s!",
    amt, objective(caster)), at);
  caster->set("death save", 0);
  remove_delayed_call("expire_me");
  remove();
  return;
}

