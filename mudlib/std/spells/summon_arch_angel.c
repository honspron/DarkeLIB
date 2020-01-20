inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","summon arch angel");
    set_property("skill","prayer");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",205);
    set_property("dev cost", 89);
    set_property("fast dev cost", 230);
    set_property("spell level", 18);
    set_property("moon","luna");
    set_property("caster message","You begin to mold the figurine into an Arch Angel.");
    set_property("target message","");
    set_property("observer message","$C begins to magically mold an alabaster figurine.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("prereq", "summon elder seraph");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell summons an Arch Angel from the most divine of the outer planes.  "
"She will serve you by guarding your tresure or fighting by you in combat.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  The spell must be cast on an alabaster figurine, which is "
"available at most magical shops.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  if(!at->id("alabaster figurine")) {
    message("info", "You must cast this spell at an alabaster figurine.",
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
  start_work(at, caster, 3000 + power*700, power);
  return;
}

void finish_work(object caster, object at, int power) {
  object ob;

  if(power <= 0) {
    message("info", "BUG in Arch Angel spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "The alabaster figurine transforms into a radiant "+
	  "Arch Angel.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "religious incantations, and an alabaster figurine "+
	  "transforms into a radiant being of light.",
	  environment(caster), ({ caster }) );
  at->remove();
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/pet/arch_angel");
  ob->set_up(power);
  ob->set_owner((string)caster->query_name());
  ob->move(environment(caster));
  remove();
  return;
}

