inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","scales of justice");

    set_property("skill","prayer");

    set_property("casting time",15);

    set_property("base mp cost",80);

    set_property("dev cost", 80);

    set_property("fast dev cost", 235);

    set_property("spell level", 15);

    set_property("moon","luna");

    set_property("caster message",

                "You invoke the scales of justice on $T.");

    set_property("target message","$C invokes the scales of justice on you.");

    set_property("observer message",

                "$C invokes the scales of justice on $T.");

    set_property("spell type",({ }));

    set_property("target type", "living");

    set_property("must be present", 1);

    set_property("duration", 25);

    set_property("stack key", "justice");

    set_property("stack num", 1);

    set_property("prereq", "protection from chaos");
    return;

}



void info() {

message("help",

"This is a very powerful spell which can serve in combat.  Basically, "

"all damage the reciepient takes in combat is also done, point for point, to his/her "

"attacker.  Note that they ALSO take full damage.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag)

{

  object ob;



  if(at->query_scales()) {

    message("info", (string)at->query_cap_name() + 

	    " already has scales of justice cast on "+objective(at)+".",

	    caster);

    caster->add_mp(props["mp cost"]);

    remove();

    return;

  }

  seteuid(getuid());

  ob = new("/std/spells/shadows/justice_shad");

  ob->start_shadow(at, props["duration"],

		   "%^CYAN%^Scales of justice wears off.%^RESET%^");

  if(flag) {

    message("info", "Somehow, you think you misdirected the energies of "+

	    "your spell.", caster);

    message("info", (string)caster->query_cap_name() + 

	    " looks puzzled.", environment(caster), ({ caster }));

    ob->set_fumble(1);

  }

  remove();

  return;

}

