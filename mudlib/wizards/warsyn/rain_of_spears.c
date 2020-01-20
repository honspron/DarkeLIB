inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name", "rain of spears");
    set_property("skill","worship of k'thach");
    set_property("casting time",6);
    set_property("base mp cost",41);
    set_property("dev cost", 52);
    set_property("fast dev cost", 151);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You cast a rain of spears!");
    set_property("target message","$C casts a rain of spears!");
    set_property("observer message","$C casts a rain of spears!");
    set_property("spell type",({ "area damage" }));
    set_property("damage multiplier", 3);
    set_property("damage types", ([ "impaling" : 30, "impaling #2" : 30,
	"impaling #3" : 30 ]));
    set_property("no target",1);
    set_property("combat spell",1);
    return;
}

void info() {
message("help",
"This spell calls forth spears from heaven to strike all enemies.",
this_player());
}
