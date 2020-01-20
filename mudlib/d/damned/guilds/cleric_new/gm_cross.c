#include <move.h>
#include <std.h>

inherit "/std/armour";
inherit AUTOLOAD;
  
void create() {
    ::create();
    set("id", ({ "cross", "necklace" }));
    set_name("cross");
    set("short", "The Cross of the Clerics");
    set("long",
"This is an ornate cross necklace worn for protection against evil.");
    set_limbs(({"head"}));
    set_weight(25);
    set_ac(1);
    set_ac(40, "disruption");
    set_wear((: call_other,this_object(), "make_me_gm" :));
    set_enh_critical(-1);
    set_value(50000);
   return;
}

int query_always_keep() { return 1; }
int make_me_gm() {
object ob;

  seteuid(getuid());
  ob= new("d/damned/guilds/cleric/cleric_obj");
  ob->make_me_master(this_player());
  return 1;
}


