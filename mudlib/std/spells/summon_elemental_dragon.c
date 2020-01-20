inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","summon elemental dragon");
    set_property("skill","elementalism");
    set_property("duration", "permanent");
    set_property("elemental spell", 1);
    set_property("casting time",4);
    set_property("base mp cost",245);
    set_property("dev cost", 110);
    set_property("fast dev cost", 332);
    set_property("spell level", 20);
    set_property("moon","luna");
    set_property("caster message","You begin to mold the figurine into an elemental.");
    set_property("target message","");
    set_property("observer message","$C begins to magically mold a platinum figurine.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("prereq", "summon greater elemental");
    return;
}

void info() {
message("help",
"This spell summons an elemental to do your bidding.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  The spell must be cast on a platinum figurine, which is "
"available at most magical shops.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  if(!at->id("platinum figurine")) {
    message("info", "You must cast this spell at a platinum figurine.",
	    caster);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the figurine!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the summoning figurine.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  set_work_message("%^CYAN%^You mold the figurine.");
  start_work(at, caster, 7200 + 900 * power, power);
  return;
}

void finish_work(object caster, object at, int power) {
  object ob;

  if(power <= 0) {
    message("info", "BUG in Elemental spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "The alabaster figurine transforms into a "+props["element"]+
	  " dragon!", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations, and an alabaster figurine "+
	  "transforms into a dragon of "+props["element"]+".",
	  environment(caster), ({ caster }) );
  at->remove();
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/elemental_dragon");
  ob->set_up(power, props["element types"], props["element"]);
  ob->set_owner((string)caster->query_name());
  ob->move(environment(caster));
  remove();
  return;
}

