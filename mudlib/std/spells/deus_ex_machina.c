#include "/adm/include/spell.h"
#include "/adm/include/daemons.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","deus ex machina");
    set_property("skill","prayer");
    set_property("casting time",45);
    set_property("base mp cost",64);
    set_property("dev cost", 110);
    set_property("fast dev cost", 300);
    set_property("spell level", 20);
    set_property("moon","luna");
    set_property("caster message","You cast deus ex machina, calling the presence of God.");
    set_property("target message","");
    set_property("observer message","$C calls upon the presence of God.");
    set_property("spell type",({ }));
    set_property("duration", 75);
    set_property("no target", 1);
    set_property("prereq", "holy mission");
    return;
}

void info() {
message("help",
"For the duration, this spell allows the caster a chance to escape death "
"once.  The chance increases with power level.  "
"It may not be stacked or used during a war.  If the caster is killed, "
"he/she may immediately resurrect, with full hp/mp!",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
//  object ob;

  if(flag) {
    message("info", "Hmm...the spell seems to have worked...", caster);
    message("info", "Everything seems fine...BUT WAIT...you are DEAD!", caster);
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
  message("info", "You may now possibly gain divine intervention.",
        caster);
  if (random(100) <= power * 15)
    {
  caster->set("death save", (: call_other, this_object(), "save_from_death" :));
      call_out("expire_me", props["duration"], caster);
    }
  return;
}

void expire_me(object me) {
  if(!me) {
    remove();
    return;
  }
  message("info", "%^CYAN%^Deus ex Machina wears off.", me);
  me->set("death save", 0);
  remove();
  return;
}

void save_from_death(object caster, object null) {
  if(!caster) return;
  caster->new_body();
  caster->heal((int)caster->query_max_hp());
  caster->add_mp((int)caster->query_max_mp());
  DAMAGE_D->stop_cont_damage(caster);
  caster->remove_paralyzed();
  message("info", "You feel the tuggings of death, but you are SAVED!",
    caster);
  message("info", CQN+" dies a horrible death.\n"
    "\n%^BOLD%^You hear a choir of angels singing and "+capitalize(nominative(caster))+
    " leaps up without a scratch!\n",
    environment(caster), ({ caster }));
  caster->set("death save", 0);
  remove_call_out("expire_me");
  remove();
  return;
}

