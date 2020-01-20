inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","summon greater elemental");
    set_property("skill","elementalism");
    set_property("elemental spell", 1);
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",125);
    set_property("dev cost", 85);
    set_property("fast dev cost", 261);
    set_property("spell level", 15);
    set_property("moon","luna");
    set_property("caster message",
        "You begin to mold the figurine into an elemental.");
    set_property("target message","");
    set_property("observer message",
        "$C begins to magically mold an golden figurine.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("prereq", "summon elemental");
    return;
}

void info() {
message("help",
"This spell summons an elemental to do your bidding.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  The spell must be cast on a golden figurine, which is "
"available at most magical shops.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  if(!at->id("golden figurine")) {
    message("info", "You must cast this spell at an golden figurine.",
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
  start_work(at, caster, 2900 + 700 * power, power);
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
  message("info", "The golden figurine transforms into a greater "+
       props["element"]+" elemental.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations, and an golden figurine "+
	  "transforms into a being of "+props["element"]+".",
	  environment(caster), ({ caster }) );
  at->remove();
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/greater_elemental");
  ob->set_up(power, props["element types"], props["element"]);
  ob->set_owner((string)caster->query_name());
  ob->move(environment(caster));
  remove();
  return;
}

