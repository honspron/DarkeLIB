inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","harm");
    set_property("skill","prayer");
    set_property("casting time",5);
    set_property("base mp cost",43);
    set_property("dev cost", 58);
    set_property("fast dev cost", 174);
    set_property("spell level", 11);
    set_property("moon","warzau");
    set_property("caster message","Your prayer is answered...$T is covered with festering boils, bleeding wounds, and watery bowels.");
    set_property("target message","A prayer from $C is answered...You are covered with festering boils, bleeding wounds, and watery bowels.");
    set_property("observer message","$C finishes a prayer for a miracle...inflicting harm upon $T");
   set_property("spell type",({ "healing" }));
    set_property("heal dice", "-10D10");
   set_property("can resist",2);
   set_property("save mod","constitution");
    set_property("must be present",1);
    set_property("combat spell", 1);
    set_property("target type", "living");
    set_property("prereq", "cause critical wounds");
    return;
}

void info() {
message("help",
"Harm is one of the most powerful offensive spells in the cleric's arsenal.  "
"It is capable of depriving an opponent of a large amount of hp (up to 200 "
"per power level), but will never kill an opponent.",
this_player());
}
