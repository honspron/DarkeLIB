inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","force shield");
    set_property("skill","energy manipulation");
    set_property("casting time",7);
    set_property("base mp cost", 40);
    set_property("dev cost", 58);
    set_property("fast dev cost", 122);
    set_property("spell level", 10);
    set_property("moon", "ankh");
    set_property("caster message",
		 "The air around $T coalesces into a hard shell.");
    set_property("target message","The air around you coalesces into a hard shell.");
    set_property("observer message",
		 "The air around $T coalesces into a hard shell.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([ "impaling" : 5, "crushing" : 10,
	"strike" : 7, "impact" : 10, "cutting" : 6]) );
    set_property("duration", 280);
    set_property("stack key", "fshield");
    set_property("stack num", 3);
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell is a nice physical damage protection spell. \n"
"The protection can be stacked thrice.",
  this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  ::spell_func(caster, at, power, args, flag);
  return;
}
