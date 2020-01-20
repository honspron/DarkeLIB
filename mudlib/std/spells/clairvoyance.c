inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","clairvoyance");
    set_property("skill","magery");
    set_property("casting time",4);
    set_property("base mp cost",12);
    set_property("dev cost", 12);
    set_property("fast dev cost", 38);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","You attempt to divine $T's location.");
    set_property("target message","You feel the presence of another mind.");
    set_property("observer message","$C seems to concentrate intesely.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("can resist", 1);
    set_property("save mod", "intelligence");
    set_property("must be present", 0);
    return;
}

void info() {
message("help",
"This spell, if successful, will accurately describe the immediate environment "
"of the target, which must be alive, as though you were seein through "
"their eyes.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
 // object ob;
//  int flag2;

  //    move_object() used here instead of move() because player is
  //    being moved right back to original location and no use in eating
  //    up useless processor time.
  if(flag) {
    remove();
    return;
  }
  if((int)at->query_level() - (int)caster->query_level() > power) {
    message("info", "The power was insufficient for a target of that level.", caster);
    remove();
    return;
  }
  message("info", "%^CYAN%^As you look through "+(string)at->query_cap_name()+
	  "'s eyes, you see:", caster);
	if(!environment(at)) {
	  message("info", "A void.", caster);
	  remove();
	  return;
	}
  message("info", "\n"+(string)environment(at)->query_long(), caster);
  remove();
  return;
}

