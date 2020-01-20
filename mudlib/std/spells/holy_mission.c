inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","holy mission");
    set_property("skill","prayer");
    set_property("casting time",35);
    set_property("base mp cost",135);
    set_property("dev cost", 95);
    set_property("fast dev cost", 281);
    set_property("spell level", 19);
    set_property("moon","luna");
    set_property("caster message",
                "You send $T on a holy mission.");
    set_property("target message","$C empowers you with a holy mission.");
    set_property("observer message",
                "$C empowers $T with a holy mission spell.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("duration", 60);
    set_property("prereq", "scales of justice");
    return;
}

void info() {
message("help",
"An extremely powerful spell, holy mission allows the recipient to fight "
"WITHOUT TAKING ANY DAMAGE for the duration of the spell.  When the spell "
"expires, however, the recipient takes ALL cumulative damage he/she would "
"have taken during the course of the spell.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob, ob2;

  if(at->query_mission()) {
    message("info", (string)at->query_cap_name() + 
	    " is already on a holy mission.",
	    caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  ob = new("/std/spells/shadows/mission_shad");
  ob2 = new("/wizards/diewarzau/obj/misc/mission_ob");
  ob2->move(at);
  ob->set_mission_ob(ob2);
  ob->start_shadow(at, props["duration"], 
		   "%^RED%^The Holy Mission ends, and you take all your "+
		   "wounds upon you.");
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
