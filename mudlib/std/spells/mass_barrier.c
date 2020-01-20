inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","elemental barrier");
    set_property("skill","elementalism");
    set_property("casting time",15);
    set_property("base mp cost",57);
    set_property("dev cost",47);
    set_property("fast dev cost",142);
    set_property("spell level", 15);
    set_property("moon","warzau");
    set_property("caster message","You cast mass barrier.");
    set_property("target message","$C casts mass barrier at you.");
    set_property("observer message","$C casts mass barrier.");
    set_property("spell type",({ "protection" }));
    set_property("elemental spell", 1);
    set_property("must be present", 1);
    set_property("ele protection", 11);
    set_property("stack key", "ele protection");
    set_property("stack num", 4);
    set_property("duration", 240);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This is an area version of 'elemental barrier' (see 'help spell elemental barrier').  It will protect all players and pets in the room, but no NPC's or monsters.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object *inv;
  object ob;

  if(caster->is_player()) {
    inv = filter_array(all_inventory(environment(caster)),
		       (: (call_other($1, $2) || call_other($1, $3)) :),
		       "is_player", "is_pet");
  } else {
    inv = filter_array(all_inventory(environment(caster)),
		       (: !(call_other($1, $2) || call_other($1, $3)) :),
			"is_player", "is_pet");
  }
  inv = distinct_array(inv+({ caster }));
  set_property("target type", "living");
  foreach(ob in inv)
    ::spell_func(caster, ob, power, args, flag);
  remove();
  return;
}


