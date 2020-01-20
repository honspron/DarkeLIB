inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","scry guard");

    set_property("skill","magery");

    set_property("casting time",12);

    set_property("base mp cost",42);

    set_property("dev cost", 62);

    set_property("fast dev cost", 180);

    set_property("spell level", 12);

    set_property("moon","luna");

    set_property("caster message","You cast scry guard on $T.");

    set_property("target message","$C casts scry guard on you");

    set_property("observer message","$C casts scry guard on $T.");

    set_property("spell type",({ }));

    set_property("duration", 180);

    set_property("target type", "living");

    set_property("must be present", 1);

    return;

}



void info() {

message("help",

"This spell makes it more difficult to scry the target.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  int mult;



  mult = 1;

  if(flag) {

    message("info", "Hmm...the spell seems to have worked...", caster);

    mult = -1;

  }

  if(at->query("scryguard")) {

    message("info", nominative(at) + " already has a scryguard...your spell fails.",

       caster);

    message("info", "%^CYAN%^"+(string)caster->query_cap_name() +

          "'s spell fails.", environment(caster), ({ caster }) );

    caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  message("info", "You are now guarded from scries...",

        at);

  at->set("scryguard", mult * 60 * power);

  call_out("expire_me", props["duration"], caster);

  return;

}



void expire_me(object me) {

  if(!me) {

    remove();

    return;

  }

  message("info", "%^CYAN%^Scry Guard wears off.", me);

  me->set("scryguard", 0);

  remove();

  return;

}



