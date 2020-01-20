#include <clock.h>
#include <daemons.h>

inherit "/std/spells/spell";

#define LESSER	0
#define NORMAL	1
#define GREATER	2
#define LORD	3

void create() {
    ::create();
    set_property("name","demon power");
    set_property("skill","chaos magic");
    set_property("casting time",14);
    set_property("base mp cost",31);
    set_property("dev cost",40);
    set_property("fast dev cost",112);
    set_property("spell level", 9);
    set_property("moon","luna");
    set_property("caster message","You cast demon power at $T.\n "
                 "Its Power flows through your viens!");
    set_property("target message","");
    set_property("observer message","$C casts demon power at $T.");
    set_property("fumble message" , "The $T cackles as $C spell fails");
    set_property("spell type",({ }));
    set_property("stack key", "demon power");
    set_property("stack num", 1);
    set_property("duration", "permanet" );  /* note: @'dawn' the spell stops */
    set_property("must be present", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell consumes the power of a demon, for the casters use.  The spell "
"must be cast at the demon itself, and the demon must be one which you have "
"summoned and successfully controlled.  The spell must be cast at a level "
"equal to or lower than the power level of the demon.  Once this spell is "
"cast at the demon, the casters stats and spell points will be increased.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  object ob;
  int demonp,mp_inc,stat_inc;

  /* the spell must be cast at a "demon" */
  if(!at->id("demon") || at->id("lesser demon")) {
    message("info", "You must cast this spell at a demon.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  /* the caster must 'own' the demon */
  if(!at->query_owner() || (string)at->query_owner() != (string)caster->query_name()) {
     message("info", "The demon must have been summoned and contolled by you.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }

  if( caster->query_property("demon power") ) {
    message("info", "You man only cast demon power one time per night",
             caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {	/* flag is set to true on a fumble */
    message("info", "Instead of using the demon's power, you release it "
      "from your control and it attacks!", caster);
    message("info", (string)at->query_cap_name() + " angrily attacks "+
          (string)caster->query_cap_name() + "!", environment(caster),
          ({ caster, at }));
    at->set_owner("asskicker");
    at->kill_ob(caster, 0);
    remove();
    return;
  }

  /* demon must be, at least, as powerful as the demon power spell */
  demonp=(int)at->query_power();
  if(demonp < power) {
    message("info", "The demon must be equal or greater power than the spell.",
             caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  /* this spell can only be cast at night! */
  if((string)EVENTS_D->query_time_of_day() != "night" ) {
    message("info", "This spell may only be cast at night.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }

  /* think about this it cost 31*power to cast :) */
  mp_inc = demonp*(random(20)+11) + 10;   /*11-30 * power of demon  + 10 */
  stat_inc = demonp * (random(10) +11); /* 11-20 * power of demon */
  ob->new("/wizards/canute/chaos_mage/demon_power_shadow.c");
  ob->set_power(mp_inc,stat_inc);
  ob->start_shadow(caster);

  message("info", "%^MAGENTA%^%^BOLD%^You consume the power of the demon.",
           caster);
  at->remove();		/* remove the demon */
  return;
}
