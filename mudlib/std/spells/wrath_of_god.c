inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","wrath of god");
    set_property("skill","worship of k'thach");
    set_property("casting time", 6);
    set_property("base mp cost", 96);
    set_property("dev cost",99);
    set_property("fast dev cost",272);
    set_property("spell level", 20);
    set_property("moon","warzau");
    set_property("caster message","You call the Wrath of GOD down!");
    set_property("target message","$C calls down the Wrath of GOD down!");
    set_property("observer message","$C calls down the Wrath of GOD.");
    set_property("spell type",({ "area damage" }));
    set_property("damage types", ([ "holy" : 40, "holy #2" : 40, "holy #3" : 40 ]));
    set_property("damage multiplier", 8);
    set_property("combat spell", 1);
    set_property("must be present", 1);
    set_property("can resist", 2);
    set_property("no target", 1);
    set_property("prereq", "retribution of k'thach");
    return;
}

void info() {
message("help",
"Perhaps the most powerful combat spell cast with 'prayer', Wrath of God calls down holy "
"energy to strike all enemies.  EXTREMELY nasty.",
this_player());
}

