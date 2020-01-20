#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;

create() {
    ::create();
    set_ac(20);
    set("id", ({ "staff", "guildmaster staff" }));
    set_name("staff");
    set("short", "a glowing white staff");
    set("long", "This staff glows with an inner light.  You cannot tell"
	" what sort of material the staff is made from but it feels "
	"pretty much unbreakable.  Who knows what sort of powers this "
	"staff has?\n ");
    set_type("two handed staff");
    set_quality(6);
    set_property("no decay",1);
    set_property("no add quality",1);
    set_wc(35, "crushing");
    set_wc(15, "electricity");
    set_wc(15, "vacuum");
    set_wc(20, "impact");
    set_verb("bludgeon");
    set_parry_bonus(25);
    set_property("enchantment",15);
    set_enh_critical(1);
    set_weight(100);
    set_value(200000);
    return;
}



int query_always_keep() { return 1; }
