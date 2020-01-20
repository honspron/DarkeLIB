inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon ethereal entity");
    set_property("skill","prayer");
    set_property("casting time",70);
    set_property("base mp cost",50);
    set_property("dev cost", 24);
    set_property("fast dev cost", 70);
    set_property("spell level", 5);
    set_property("moon","luna");
    set_property("caster message","You summon an ethereal entity to do your bidding.");
    set_property("target message","");
    set_property("observer message","$C utters some clerical incantations and an ethereal entity appears.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 900);
    set_property("prereq", "summon aerial servant");
    return;
}

void info() {
message("help",
"This spell summons an Ethereal Entity, a potent spirit which can aid you in "
"combat.  You command the entity the same way you talk to NPC's...see "
"'help communication'.  Tell it help for help on commanding it.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/ethereal_entity");
  ob->set_up(power);
  ob->move(environment(caster));
  if(!flag)
    ob->set_owner((string)caster->query_name());
  ob->set_dur(props["duration"]);
  if(flag) {
    message("info", "Your fumble has caused the ethereal entity to become "+
	    "hostile!", caster);
    message("info", "The ethereal entity is disoriented and becomes hostile!",
	     environment(caster), ({ caster }) );
    ob->kill_ob(caster, 0);
    remove();
    return;
  }
  ob->set_owner((string)caster->query_name());
  remove();
  return;
}

