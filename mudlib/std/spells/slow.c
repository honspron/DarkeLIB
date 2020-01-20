#include <spell.h>



inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","slow");

    set_property("skill","magery");

    set_property("casting time",4);

    set_property("base mp cost",37);

    set_property("dev cost", 25);

    set_property("fast dev cost", 73);

    set_property("spell level", 5);

    set_property("moon","luna");

    set_property("caster message","You cast slow at $T.");

    set_property("target message","$C casts slow at $T");

    set_property("observer message","$C casts slow at you!");

    set_property("spell type",({ }));

    set_property("target type", "living");

    set_property("combat spell", 1);

    set_property("must be present", 1);

    set_property("duration", 60);

    set_property("can resist", 1);

    set_property("save mod", "strength");

    return;

}



void info() {

message("help",

"This spell, when cast on a target, slows the target significantly.  "

"The target may still attack and perform actions at the normal rate, "

"but movement is delayed.  When the target types a direction command, "

"he/she must wait 5 seconds for it to take effect.  Power affects "

"duration and resist chance only.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  object ob, ob2;



  if(flag) {

    at = caster;

    message("info", "You slow yourself!", caster);

    message("info", CQN+"'s spell goes off at "+

      objective(caster)+"self!", EC, ({ caster }));

  }

  if(at->query_slow()) {

    message("info", "A recipient may only have 1 slow spell at a time.",

      caster);

    if(!flag) caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  ob=new("/wizards/diewarzau/obj/misc/slow_ob");

  at->set("exits", (string *)environment(at)->query_exits());

  ob->move(at);

  ob2 = new("/std/spells/shadows/slow_shadow");

  ob2->set_slow_ob(ob);

  ob2->start_shadow(at, props["duration"], "%^CYAN%^A slow spell wears off.");

  remove();

  return;

}

