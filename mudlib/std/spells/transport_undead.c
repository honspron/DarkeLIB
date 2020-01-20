#include <daemons.h>

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","transport undead");
    set_property("skill","necromancy");
    set_property("casting time",67);
    set_property("base mp cost",67);
    set_property("dev cost", 17);
    set_property("fast dev cost", 52);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","You cast transport undead at $T.");
    set_property("target message","");
    set_property("observer message","$C casts transport undead at $T.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("duration", "instantaneous");
    set_property("prereq", "undead dimension");
    return;
}

void info() {
message("help",
"This spell allows your undead servants to be saved past reboots and when you log "
"off.  It transports the target (which must be an undead creature summoned by "
"you) to another plane where it will await you.  You must cast 'undead dimension' "
"to transport yourself to the dimension and retrieve your waiting servants.  "
"The power level of the spell times four must be equal to or greater than the level of the "
"monster.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
//  object room;
  
  if(!at->is_pet() || (string)at->query("race") != "undead" ||
      (string)at->query_owner() != (string)caster->query_name()) {
    message("info", "You must cast this spell at an undead creature that "
          "YOU control.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You accidentally transport your servant away, never to "+
        "be heard from again!", caster);
    at->remove();
    remove();
    return;
  }
  if(power*4 < (int)at->query_level()) {
    message("info", "The power of this spell is insufficient to transport a "
        "creature of that level.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->move(sprintf("/d/damned/virtual/%s.undead",
      (string)caster->query_name()));
  SAVE_ITEMS_D->update_lockers(environment(at));
  message("info", "%^GREEN%^%^BOLD%^"+(string)at->query_short() + " disappears.",
	environment(caster));
  message("info", (string)at->query_short() + " has been saved in "+
        "your undead dimension, and will await your return.", caster);
  remove();
  return;
}

