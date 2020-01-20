inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","armour of oblivion");
    set_property("skill","energy manipulation");
    set_property("casting time",16);
    set_property("base mp cost", 75);
    set_property("dev cost", 88);
    set_property("fast dev cost", 174);
    set_property("spell level", 17);
    set_property("moon", "ankh");
    set_property("caster message",
		 "The image of $T shimmers behind an energy void.");
    set_property("target message","An energy void shimmers around you.");
    set_property("observer message",
		 "The image of $T shimmers behind an energy void.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([ "fire" : 120, "cold" : 120,
	"electricity" : 120, "vacuum" : 120, "holy" : 120, "disruption" : 120,
                                      	   			]) );
    set_property("duration", 30);
    set_property("prereq", "energy shield");
    set_property("stack key", "ram");
    set_property("stack num", 2);
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell is the be all, end all of magical protection spells. "
"The protection is very SICK and can be stacked twice.",
  this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  ::spell_func(caster, at, power, args, flag);
  return;
}

