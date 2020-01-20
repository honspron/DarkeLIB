#include <move.h>

inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","stabilize familiar");
    set_property("skill","magery");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",235);
    set_property("dev cost", 82);
    set_property("fast dev cost", 240);
    set_property("spell level",17);
    set_property("moon","luna");
    set_property("caster message","You begin to mold the figurine into a familiar.");
    set_property("target message","");
    set_property("observer message","$C begins to magically mold a platinum figurine.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("prereq", "summon greater familiar");
    return;
}

void info() {
message("help",
"This spell creates a magical figurine which may then be used to make a "
"familiar or greater familiar permanent.  You must cast this spell at a "
"power equal to or greater than the power of the familiar you wish to "
"stabilize.  "
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
  start_work(at, caster, 2000 + power*950, power);
  return;
}

void finish_work(object caster, object at, int power) {
  object ob;

  if(power <= 0) {
    message("info", "BUG in stablilize familiar spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "The jeweled figurine transforms into the likeness of "+
        "a familiar.\nYou may stabilize any familiar by typing "+
        "'stabilize <name>' where <name> is the name of the familiar.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations, and a jeweled figurine takes the form of an animal.",
	  environment(caster), ({ caster }) );
  at->remove();
  seteuid(getuid());
  ob = new("/wizards/diewarzau/obj/misc/familiar_fig");
  ob->set_up(power);
  if((int)ob->move(caster) != MOVE_OK)
    ob->move(environment(caster));
  remove();
  return;
}

