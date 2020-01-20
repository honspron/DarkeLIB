#include <move.h>
#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;
  
void create() {
    ::create();
    set("id", ({ "maul", "gah k'zan", "hammer", "maul of the guildmaster" }));
    set("short", "Gah K'zan, the Maul of the Guildmaster");
    set("long",
"This huge maul is crafted of an unearthly metal.  It is extremely enchanted!");
    set_weight(160);
    set_type("two handed blunt");
    set_wc(30, "crushing");
    set_wc(15, "impact");
    set_ac(20);
    set_parry_bonus(-10);
    set_quality(6);
    set_property("no add quality", 1);
    set_property("no decay", 1);
    set_property("enchantment", 20);
    set_wield((: call_other,this_object(), "make_me_gm" :));
    set_enh_critical(2);
    set_value(132);
   return;
}

string *query_auto_critical() {
  if(random(100) < 25) return ({ sprintf("impact %s", ({ "A", "B", "C" })[random(3)]) });
  else return ({});
}

int query_always_keep() { return 1; }
int make_me_gm() {
object ob;

  seteuid(getuid());
  ob= new("d/damned/guilds/tinker/tinker_obj");
  ob->make_me_master(this_player());
  return 1;
}


