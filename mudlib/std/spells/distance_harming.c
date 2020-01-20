inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","distance harming");
    set_property("skill","prayer");
    set_property("casting time",18);
    set_property("base mp cost",55);
    set_property("dev cost", 68);
    set_property("fast dev cost", 204);
    set_property("spell level", 14);
    set_property("moon","warzau");
    set_property("caster message","Your prayer is answered...$T is covered with festering boils, bleeding wounds, and watery bowels.");
    set_property("target message","A prayer from $C is answered...You are covered with festering boils, bleeding wounds, and watery bowels.");
    set_property("target message","$C casts a harming spell upon you.");
    set_property("observer message","$C finishes a prayer for a miracle...inflicting harm upon $T");
    set_property("target observer message","Suddenly, $T is covered with festering boils, bleeding wounds, and squirting bowels.");
    set_property("spell type",({ "healing" }));
    set_property("heal dice", "-20D6");
   set_property("can resist",2);
   set_property("save mod","constitution");
    set_property("target type", "living");
    set_property("combat spell", 1);
    set_property("prereq", "harm");
    return;
}

void spell_func(object caster, object at, int power, string args, int flag) 
{
if(environment(at)->query_property("no scry"))
	{
	message("spell", "They seemed to be protected by a mystical field.", caster);
        remove();
        return;
	}
::spell_func(caster, at, power, args, flag);

}





void info() {
message("help",
"This spell is a slightly less potent version of the 'harm' spell, except "
"that the receipient may be anywhere on the mud.  The recipient can be "
"a player or monster, but keep in mind that it might get the wrong monster "
"if there are two identically named monsters on the mud.",
this_player());
}
