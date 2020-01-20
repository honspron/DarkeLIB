#include <spell.h>



inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","shields of war");

    set_property("skill","worship of k'thach");

    set_property("casting time",11);

    set_property("base mp cost",38);

    set_property("dev cost", 71);

    set_property("fast dev cost", 205);

    set_property("spell level", 14);

    set_property("moon","luna");

    set_property("caster message","You cast shields of war.");

    set_property("target message","");

    set_property("observer message","$C casts shields of war.");

    set_property("spell type",({ }));

    set_property("no target", 1);

    set_property("duration", 120);

    set_property("prereq", "battle fury");
    return;

}



void info() {

message("help",

"This spell summons magical barriers which float about the caster, "

"blocking incoming attacks.  Unlike armour, these barriers do NOT "

"reduce damage.  Rather, they have a chance (which depends on power "

"level) of blocking any given attack COMPLETELY.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  object ob;



  seteuid(getuid());

  at = caster;

  if(at->query_shields_of_war()) {

    message("info", "This spell may not be stacked.",

      caster);

    caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  if(flag) {

    message("info", "The shields spin out of control, pummeling you!",

      caster);

    message("info", "The barriers summoned by "+CQN+"'s spell "+

      "ruthlessly pummel "+objective(caster)+"!", EC,

      ({ caster }));

    do_critical(({ "impact C" }), caster, caster);

    remove();

    return;

  }

   ob = new("/std/spells/shadows/w_shield_shad.c");

  ob->set_level(power);

  ob->start_shadow(at, props["duration"], "%^CYAN%^Shields of War expires.");

   ::spell_func(caster, at, power, args, flag);

   remove();

  return;

}

