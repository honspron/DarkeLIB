inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","satisfy thirst");

    set_property("skill","body alteration");

    set_property("casting time",12);

    set_property("base mp cost",7);

    set_property("dev cost", 6);

    set_property("fast dev cost", 18);

    set_property("spell level", 1);

    set_property("moon","luna");

    set_property("caster message",

		 "You cast satisfy thirst at $T....yum.");

    set_property("target message","$C casts a spell, satisfying your thirst.");

    set_property("observer message",

		 "$C casts satisfy thirst at $T.");

    set_property("spell type",({ }));

    set_property("target type", "living");

    set_property("must be present", 1);

    return;

}



void info() {

message("help",

"This spell is capable of substituting for drink in that it satisfies "

"the target's thirst.  Drinking helps regenerate hp and mp.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {



  if(flag) {

    message("info", "You end up giving "+(string)at->query_cap_name()+

	    " a nasty case of indigestion!", caster);

    message("info", (string)caster->query_cap_name() + " ends up giving you "+

	    " terrible indigestion!", at);

    at->heal(-5);

    remove();

    return;

  }

  if(!at->add_quenched((15 + random(10)) * power))

     message("info", (string)at->query_cap_name()+ " is completely full.",

	     caster);

  remove();

  return;

}





