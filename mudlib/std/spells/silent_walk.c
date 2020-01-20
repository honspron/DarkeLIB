#include <spell.h>



inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","silent walk");

    set_property("skill","illusionism");

    set_property("casting time",11);

    set_property("base mp cost",25);

    set_property("dev cost", 14);

    set_property("fast dev cost", 41);

    set_property("spell level", 3);

    set_property("moon","luna");

    set_property("caster message","You begin to walk silently.");

    set_property("target message","");

    set_property("observer message","$C begins to walk silently.");

    set_property("spell type",({ }));

    set_property("no target", 1);

    set_property("duration", 240);

    return;

}



void info() {

message("help",

"This spell allows silent walking, similar to the stealth skill.  "

"You may still be seen, but entry into the room will be unannounced on a "

"successful contest of skills with the listener's perception.  If you have the "

"stealth skill, the effects of this spell ARE cumulative with it.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  object ob;



  if(flag) {

    message("info", "Odd, everything seems to have worked okay...",

      caster);

    message("shout", "The DemiUrge shouts: "+CQN+" the "+(string)caster->query_class()+" is moving "+

      "about stealthily.  If you want to catch him, he is in "+

      (string)environment(caster)->query_short()+".", users(), ({ caster }));

    remove();

    return;

  }

  if(caster->query_mag_stealth()) {

    message("info", "This spell cannot be stacked.", caster);

    caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  ob = new("/std/spells/shadows/mag_stealth_shadow");

  ob->set_my_skill(20+power*15);

  ob->start_shadow(caster, props["duration"], "%^CYAN%^Silent walk wears off.");

  remove();

  return;

}

