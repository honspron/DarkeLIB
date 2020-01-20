inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon illusionary guardian");
    set_property("skill","illusionism");
    set_property("casting time",4);
    set_property("base mp cost",55);
    set_property("dev cost",51);
    set_property("fast dev cost",150);
    set_property("spell level", 10);
    set_property("moon","luna");
    set_property("caster message","You summon an illusionary guardian.");
    set_property("target message","");
    set_property("observer message","$C sumons an illusionary guardian.");
    set_property("spell type",({  }));
    set_property("duration", 360);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This is a powerful spell which summons an illusionary pet.  The pet takes "
"The form of an Arch Angel, a Vacid Dragon, or a Dracolich (randomly).  "
"It may be set to aggressive just like a normal pet, but it will do NO damage, "
"but anyone who steps into the room will THINK they are taking damage, down to "
"fake hit point reports!  The illusion will be dispelled after a few hits (more "
"with greater power level, but it is useful for blocking exits and wreaking general "
"havoc...",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
//  int roll;

  seteuid(getuid());
  if(flag) {
    message("info", "Oops, you summon a REAL Dracolich, and he attacks you!",
      caster);
    ob = new("/wizards/diewarzau/obj/pet/dracolich");
    ob->set_up(power);
    ob->set_owner("asskicker");
    ob->set_aggr_status(1);
    ob->move(environment(caster));
    ob->kill_ob(caster);
    ob->set_speed(60);
    ob->set_moving(1);
    remove();
    return;
  }
  ob = new("/wizards/diewarzau/obj/pet/guardian");
  ob->set_hits((4+random(6))*power);
  ob->set_up(random(3)+1);
  ob->move(environment(caster));
  ob->set_owner((string)caster->query_name());
  ob->set_dur(props["duration"]);
  message("info", "%^GREEN%^%^BOLD%^"+(string)ob->query_short()+
    " appears.", environment(caster));
  remove();
  return;
}

