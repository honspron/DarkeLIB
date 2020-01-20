inherit "/std/spells/spell";

object shad;

void create() {
    ::create();
    set_property("name","alter visage");
    set_property("skill","illusionism");
    set_property("casting time",12);
    set_property("base mp cost",38);
    set_property("dev cost", 22);
    set_property("fast dev cost", 63);
    set_property("spell level", 5);
    set_property("moon","luna");
    set_property("caster message","You cast alter visage.");
    set_property("target message","");
    set_property("observer message","$C casts alter visage.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 122);
    return;
}

void info() {
message("help",
"This spell magically disguises you as another player on the mud.  "
"You may ONLY disguise yourself as another player online.  The higher "
"the power of the spell, the greater the chance of fooling people with the "
"disguise.\n"
"Syntax: cast *3 disguise at <player>",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  if(!args || !stringp(args)) {
    message("info", "See 'help spell alter visage' for "+
      "syntax.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!(ob=find_player(lower_case(args)))) {
    message("info", "Cannot find the player '"+args+"'.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(objectp(caster->query("disguise shad"))) {
    message("info", "You are already disguised.  You must remove the disguise or wait until the spell "+
      "expires, as appropriate.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "The spell seems to have worked okay.",
      caster);
    message("shout", "HEY EVERYONE: "+(string)caster->query_cap_name()+
      " has just disguised himself as "+capitalize(args)+"!!!",
      users(), ({ caster }));
  }
  seteuid(getuid());
  shad = new("/std/spells/shadows/disguise_shad");
  shad->set_new_short((string)ob->query_short());
  shad->set_new_cap_name(capitalize((string)ob->query_name()));
  shad->start_shadow(caster);
  shad->set_my_skill(20*power);
  caster->set("disguise shad", shad);
  call_out("remove_disguise", props["duration"], caster);
}

void remove_disguise(object caster) {
  object ob;
  
  if(!caster) return;
  if(!shad || (object)caster->query("disguise shad") != shad)
    return;
  caster->set("disguise shad", 0);
  shad->external_destruct(shad);
  message("info", "%^CYAN%^Alter visage wears off.", caster);
  message("info", "A disguise spell dissolves, revealing "+
    (string)caster->query_cap_name()+" beneath!",
    environment(caster), ({ caster }));
  remove();
  return;
}
