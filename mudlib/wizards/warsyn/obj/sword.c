inherit "/std/weapon";

create() {
    ::create();
    set_ac(20);
    set("id", ({ "sword", "guildmaster sword", "ran-khar" }));
    set_name("ran-khar");
    set("short", "Ran-Khar, the Sword of the Guildmaster");
    set("long", "Truly, this is one of the best blades you have ever "
        "laid eyes on.  The blade is sparkling silver mithril, and the hilt "
        "is crafted of gold and leather and encrusted with jewels.  The "
        "magical aura about the object is so powerful that it may be sensed "
        "even by the layman." );
    set_type("blade");
    set_quality(6);
    set_property("no decay",1);
    set_property("no add quality",1);
    set_wc(35, "cutting");
    set_wc(10, "impaling");
    set_verb("slice");
    set_parry_bonus(5);
    set_property("enchantment",15);
    set_enh_critical(2);
    set_weight(350);
    set_value(143060);
    set_material("metal/mithril");
    return;
}
