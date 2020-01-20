inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name", "dagger storm");
    set_property("skill","conjuration");
    set_property("casting time",5);
    set_property("base mp cost",30);
    set_property("dev cost", 65);
    set_property("fast dev cost", 150);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You cast ice daggers at $T!");
    set_property("target message","$C casts ice daggers upon you!");
    set_property("observer message","$C casts ice daggers at $T!");
    set_property("spell type",({ "damage" }));
    set_property("damage types", ([ "impaling" : 40, "impaling #2" : 40,
	"impaling #3" : 40, "cutting" : 50, "cutting #2" : 50]));
    set_property("must be present",1);
    set_property("combat spell",1);
    return;
}

void info() {
message("help",
"This spell casts ice daggers at the foe, shredding him most heinously.",
this_player());
}
