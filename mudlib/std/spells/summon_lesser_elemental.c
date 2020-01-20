inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon lesser elemental");
    set_property("skill","elementalism");
    set_property("casting time",62);
    set_property("base mp cost",48);
    set_property("dev cost", 27);
    set_property("fast dev cost", 77);
    set_property("spell level", 4);
    set_property("moon","luna");
    set_property("caster message","You summon a lesser elemental to do your bidding.");
    set_property("target message","");
    set_property("observer message","$C utters some magical incantations and a lesser elemental appears.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 600);
    set_property("elemental spell", 1);
    return;
}

void info() {
message("help",
"This spell summons a lesser elemental to help you in combat.  "
"You command the elemental the same way you talk to NPC's...see "
"'help communication'.  Say help to it for help on commanding it.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/lesser_elemental");
  ob->set_up(power, props["element types"], props["element"]);
  ob->move(environment(caster));
  if(!flag)
    ob->set_owner((string)caster->query_name());
  ob->set_dur(props["duration"]);
  if(flag) {
    message("info", "Your fumble has caused the elemental to become "+
	    "hostile!", caster);
    message("info", "The elemental is disoriented and becomes hostile!",
	     environment(caster), ({ caster }) );
    ob->kill_ob(caster, 0);
    remove();
    return;
  }
  ob->set_owner((string)caster->query_name());
  remove();
  return;
}

