#include "/adm/include/spell.h"

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","body of elements");
    set_property("skill","elementalism");
    set_property("elemental spell", 1);
    set_property("casting time",14);
    set_property("base mp cost",25);
    set_property("dev cost", 6);
    set_property("fast dev cost", 19);
    set_property("spell level", 1);
    set_property("moon","ankh");
    set_property("caster message","You cast body of elements.");
    set_property("target message","");
    set_property("observer message","$C casts body of elements.");
    set_property("spell type",({ "stat mod", "skill mod", "protection" }));
    set_property("stat dice", "1D6");
    set_property("skill dice", "1D8");
    set_property("ele protection", 7);
    set_property("stats", ({ "strength", "intelligence", "dexterity" }) );
    set_property("no target", 1);
    set_property("must be present",1);
    set_property("duration", 240);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell transforms the caster's body into the form of the element "
"chosen.  The caster will receive a substantial bonus in melee skill as "
"well as bare-handed damage of the element chosen.  The caster will also "
"receive mild protection from the element as well as a skill bonus to "
"the lore skill of that element.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "You misdirect the spell, calling the element upon "+
      "yourself!", caster);
    message("info", CQN+" misdirects "+possessive(caster)+" spell, "+
      "calling the wrath of "+props["element"]+" on "+objective(caster)+
      "self!", EC, ({ caster }));
    do_critical(caster, caster, map_array(props["element types"], (: $1 + $2 :),
      " B"));
    remove();
    return;
  }
  if((int)caster->query_d_trans()) {
    message("info", (string)caster->query_cap_name() +
	    " has already been transformed by a body transformation spell.",
	    caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/e_trans_shadow");
  ob->set_melee(8 + power *2);
  ob->set_melee_skill(15+power*2);
  ob->set_elements(props["element types"]);
  ob->start_shadow(caster, props["duration"],
		   "%^CYAN%^Body of elements wears off.");
  message("info", "You transform your body into the form of "+props["element"]+
	  ".", caster);
  message("info", CQN+" transforms into a being of "+props["element"]+"!",
	  EC, ({ caster }));
  set_property("skills", ({ "elementalism", sprintf("%s lore", 
						    props["element"]) }));
  ::spell_func(caster, caster, power, args, 0);
  return;
}

