inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","magic missile");
    set_property("skill","conjuration");
    set_property("casting time",2);
    set_property("base mp cost",10);
    set_property("dev cost", 7);
    set_property("fast dev cost", 18);
    set_property("spell level", 1);
    set_property("moon","warzau");
    set_property("caster message","You cast magic missile at $T.");
    set_property("target message","$C casts magic missile at you!");
    set_property("observer message","$C casts magic missile at $T.");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "impact" : 15 ]));
    set_property("damage multiplier", 1.3);
    set_property("can resist", 2);
    set_property("save mod", "dexterity");
    set_property("must be present", 1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This spell allows the caster to hurl magic missile at the target.  One missile is thrown for "
"every five levels of the caster.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int i, max;
  mapping dmg;

  max = 1+(int)caster->query_level()/5;
  if(max > 10) max = 10;
  dmg = ([]);
  for(i = 1; i <= max; i++)
    dmg += ([ sprintf("impact #%d", i) : 15 ]);
  set_property("damage types", dmg);
  ::spell_func(caster, at, power, args, flag);
  return;
}

  
