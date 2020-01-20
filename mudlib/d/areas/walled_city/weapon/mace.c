/* Weapon coded by Duridian for DarkeMud. */
 
#include <std.h>
inherit WEAPON;
 
void create() {
   ::create();
   set_name("mace");
   set("id", ({"mace"}) );
   set("short", "mace");
   set("long",
   "This mace features a heavy spiked ball on the end of a short "
   "handle.  It looks like an effective instrument for causing bodily "
   "damage."
   );
   set_weight(300);
   set_value(75);
   set_type("blunt");
   set_wc(13, "crushing");
   set_ac(3);
   set_quality(3);
   set_verb("pound");
}
