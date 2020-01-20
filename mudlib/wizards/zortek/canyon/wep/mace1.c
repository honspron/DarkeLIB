inherit "/std/weapon";

create() {
    ::create();
    set_ac(30);
    set("id", ({ "mace" }) );
    set_short("Footman's Mace");
    set_long(@TEXT
This footmans mace is a standard field weapon.
TEXT
);
    set_type("blunt");
    set_quality(6);
    set_property("light", 1);
    set_property("no add quality",1);
    set_wc(25, "disruption");
    set_verb("crack");
    set_parry_bonus(20);
    set_property("enchantment",30);
    set_value(50000);
    set_enh_critical(4);
    return;
}
