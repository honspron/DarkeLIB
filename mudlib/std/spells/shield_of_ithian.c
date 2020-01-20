inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","shield of ithian");

    set_property("skill","energy manipulation");

    set_property("casting time",16);

    set_property("base mp cost", 80);

    set_property("dev cost", 98);

    set_property("fast dev cost", 194);

    set_property("spell level", 18);

    set_property("moon", "ankh");

    set_property("caster message",

		 "An impenetrable shell forms around $T.");

    set_property("target message","An invisible shell forms around you. You feel very protected.");

    set_property("observer message",

		 "The air shimmers for a second and now $T looks somehow untouchable.");

    set_property("spell type",({ "protection" }));

    set_property("target type", "living");

    set_property("protection types", ([ "impaling" : 120, "crushing" : 120,

	"strike" : 120, "impact" : 120, "cutting" : 120,

                                      	   			]) );

    set_property("duration", 30);

    set_property("prereq", "force shield");
    set_property("stack key", "rap");

    set_property("stack num", 2);

    set_property("must be present", 1);

    return;

}



void info() {

message("help",

"This spell is the be all, end all of physical protection spells. \n"

"The protection(physical damage) is very SICK and can be stacked twice.",

  this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {



  ::spell_func(caster, at, power, args, flag);

  return;

}

