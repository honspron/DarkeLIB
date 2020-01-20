inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon aerial servant");
    set_property("skill","prayer");
    set_property("casting time", 45);
    set_property("base mp cost",45);
    set_property("dev cost", 24);
    set_property("fast dev cost", 70);
    set_property("spell level", 5);
    set_property("moon","luna");
    set_property("caster message","You summon an aerial servant to do your bidding.");
    set_property("target message","");
    set_property("observer message","$C utters some clerical incantations and an aerial servant appears.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 900);
    return;
}

void info() {
message("help",
"This spell summons a lesser spirit called an aerial servant.  The servant "
"can carry objects for you if you are overly encumbered.  You command the "
"servant in the same way you speak to all other NPC's (see 'help "
"communication').  Tell the servant 'help' to see what it can do.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/aerial_servant");
  ob->set_up(power);
  ob->move(environment(caster));
  if(!flag)
    ob->set_owner((string)caster->query_name());
  ob->set_dur(props["duration"]);
  if(flag) {
    message("info", "Your fumble has caused the aerial servant to become "+
	    "hostile!", caster);
    message("info", "The aerial servant is disoriented and becomes hostile!",
	     environment(caster), ({ caster }) );
    ob->kill_ob(caster, 0);
  }
  remove();
  return;
}

