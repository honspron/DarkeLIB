inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon guardian angel");
    set_property("skill","prayer");
    set_property("casting time",41);
    set_property("base mp cost",55);
    set_property("dev cost",56);
    set_property("fast dev cost",150);
    set_property("spell level", 11);
    set_property("moon","luna");
    set_property("caster message","You summon a Guardian Angel.");
    set_property("target message","");
    set_property("observer message","$C sumons a Guardian Angel.");
    set_property("spell type",({  }));
    set_property("duration", 340);
    set_property("no target", 1);
    set_property("prereq", "summon ethereal entity");
    return;
}

void info() {
message("help",
"This spell summons a guardian angel to serve the caster.  "
"Unlike most other pets, the angel will defend the caster during "
"combat by blocking attackers!!!  Stronger attackers are more difficult to "
"block.  The guardian angel will also fight, but its fighting "
"skills are meager, and it is mostly defensive.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
//  int roll;

  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/guardian_angel");
  ob->set_dur(props["duration"]);
  ob->set_owner("asskicker");
  ob->set_up(power);
  ob->move(environment(caster));
  if(flag) {
    message("info", "%^RED%^%^BOLD%^The angel is disoriented...it angrily attacks you!", caster);
    message("info", "%^RED%^%^BOLD%^The angel angrily attacks "+
      (string)caster->query_cap_name()+"!", environment(caster), ({ caster }));
    ob->kill_ob(caster, 0);
    ob->set_aggr_status(1);
    caster->add_follower(ob);
    remove();
    return;
  }
  ob->set_owner((string)caster->query_name());
  remove();
  return;
}

