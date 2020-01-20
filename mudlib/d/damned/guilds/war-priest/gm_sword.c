#include <move.h>
#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;
  
void create() {
    ::create();
    set("id", ({ "sword", "zansera", "sword of the guildmaster" }));
    set("short", "Tu'enmat, Blade of K'thach");
    set("long",
                "The air seems to shimmer about this blade.  Warm to the "
                "touch, this mighty weapon can reek destruction upon "
                "the foes of its wielder.  Upon the blade is the word "
                "'Tu'enmat', although you do not recognize the language that "
                "it is written in, you are able to understand the writing." 
        );
    set_material("metal/mithril");
    set_weight(120);
    set_wc(30, "cutting");
    set_wc(15, "vacuum");
    set_wc(20, "holy");
    set_type("two handed blade");
    set_quality(6);
    set_property("no add quality", 1);
    set_property("no decay", 1);
    set_property("brittle", 15);
    set_ac(20);
    set_parry_bonus(20);
    set_property("enchantment", 20);
    set_enh_critical(2);
    set_value(132);
    return;
}
