inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","energy shield");
    set_property("skill","energy manipulation");
    set_property("casting time",7);
    set_property("base mp cost", 25);
    set_property("dev cost", 48);
    set_property("fast dev cost", 102);
    set_property("spell level", 9);
    set_property("moon", "ankh");
    set_property("caster message",
		 "A small shield of energy forms around $T. ");
    set_property("target message","A small energy shield forms around you.");
    set_property("observer message",
		 "A small shield of energy forms around $T.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([ "fire" : 7, "cold" : 7,
	"electricity" : 10, "vacuum" : 7, "holy" : 5, "disruption" : 5]) );
    set_property("duration", 280);
    set_property("stack key", "eshield");
    set_property("stack num", 3);
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell is a kewl magical protection spell.  It protects against all "
"forms of common magical attack.  The protection can be stacked thrice.",
  this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  ::spell_func(caster, at, power, args, flag);
  return;
}

