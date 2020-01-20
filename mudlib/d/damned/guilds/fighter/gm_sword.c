#include <std.h>

inherit "/std/weapon";
inherit AUTOLOAD;

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
    set_wc(32, "cutting");
    set_wc(10, "impaling");
    set_wc(10, "electricity");
    set_wc(10, "vacuum");
    set_verb("slice");
    set_material("metal/mithril");
    set_parry_bonus(10);
    set_wield( (: call_other, this_object(), "make_me_gm" :) );
    set_property("enchantment",20);
    set_enh_critical(2);
    set_weight(200);
    set_value(60);
    return;
}

int query_always_keep() { return 1; }
int make_me_gm() {
  object ob;

  //  the function below will handle all necessary checking, etc.
  seteuid(getuid());
  ob = new("/d/damned/guilds/fighter/fighter_obj");
  ob->make_me_master(this_player());
  return 1;
}


