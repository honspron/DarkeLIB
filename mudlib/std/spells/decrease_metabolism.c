inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","decrease metabolism");
    set_property("skill","body alteration");
    set_property("casting time",10);
    set_property("base mp cost",45);
    set_property("dev cost", 64);
    set_property("fast dev cost", 155);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message",
                "You cast decrease metabolism on $T.");
    set_property("target message","$C casts decrease metabolism on you!");
    set_property("observer message",
                "$C casts decrease metabolism on $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("can resist", 1);
    set_property("save mod", "constitution");
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("duration", 120);
    return;
}

void info() {
message("help",
"This spell decreases the target's metabolism, including the rate of healing, "
"the rate of fighting, etc.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob;

  if(at->query_metabolism()) {
    message("info", (string)at->query_cap_name() + 
	    " already has a metabolic spell cast on "+objective(at)+".",
	    caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  ob = new("/std/spells/shadows/metabolism_shad");
  ob->set_met_rate((flag?-1:1)*power*12);
  ob->start_shadow(at, props["duration"], "Decrease metabolism wears off.");
  if(flag) {
    message("info", "Somehow, you think you misdirected the energies of "+
	    "your spell.", caster);
    message("info", (string)caster->query_cap_name() + 
	    " looks puzzled.", environment(caster), ({ caster }));
  }
  remove();
  return;
}
