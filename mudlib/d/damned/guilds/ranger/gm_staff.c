#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;

create() {
    ::create();
    set_ac(10);
    set("id", ({ "staff", "quarter staff" }));
    set_name("staff");
    set("short", "A simple looking staff");
    set("long", "This is a simple looking metal staff, it doesn't look all
that powerful.  You have no idea why anyone would want to use this.\n");
    set_type("two handed staff");
    set_quality(6);
    set_property("no decay",1);
    set_property("no add quality",1);
    set_wc(20, "crushing");
    set_verb("bludgeon");
    set_parry_bonus(15);
    set_property("enchantment",15);
    set_material("metal/catoetine");
    add_enchantment("earth", "greater elemental blade", 6, 2500, "earth");
    add_enchantment("earth2", "greater essential blade", 6, 2500, "earth");
    add_enchantment("earth3", "greater essential blade", 6, 2500, "earth");
    set_enh_critical(1);
    set_weight(100);
    set_value(200000);
    return;
}
