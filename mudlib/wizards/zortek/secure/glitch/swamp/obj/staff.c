/* Staff */

#include <std.h>
inherit WEAPON;

void create() {
	mixed str;
	::create();
	set_name("long polished metal staff");
	set("id", ({"staff","metal staff","polished metal staff"}) );
	set("short","a polished metal staff");
	set("long",
	"The very fine looking metal staff has been polished to a high sheen. "
	"It almost seems to give off a light of it's own.");
	set_weight("250");
	set_value("7500");
	set_type("two handed staff");
	set_ac(12);
	set_wc(15, "electricity");
	set_wc(15, "fire");
	set_wc(15, "cold");
	set_wc(15, "plasma");
	set_wc(45, "blunt");
	set_property("no add quality", 1);
	set_quality(6);
	set_parry_bonus(10);
	set_decay_rate(3000);
	set_property("enchantment", 1);
	set_property("extra long", str);
	set_material("metal/mabril");
}
