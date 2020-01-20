#include <move.h>
#include <std.h>

inherit "/std/armour";
inherit AUTOLOAD;
  
create() {
    ::create();
    set("id", ({ "helm", "helmet" }));
    set("short", "The dark helm of Darkryl");
    set("long",
"This helm is ");
    set_limbs(({"head"}));
    set_weight(100);
    set_ac(40);
    set_wear((: call_other,this_object(), "make_me_gm" :));
    set_ac(50, "holy");
    set_enh_critical(-1);
    set_value(100000);
   return;
}

int query_always_keep() { return 1; }
int make_me_gm() {
object ob;

  seteuid(getuid());
  ob= new("d/damned/guilds/chaotic-lord/chaotic-lord_obj");
  ob->make_me_master(this_player());
  return 1;
}


