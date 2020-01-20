#include <std.h>

inherit WEAPON;
inherit AUTOLOAD;

create() {
    ::create();
    set_ac(20);
    set_name("dagger");
    set("id", ({ "dagger", "guildmaster dagger", "grey dagger", "dagger of aaaargh" }));
    set("short", "The Legendary Black Dagger of Aaaargh");
    set("long", 
"This is a long, curved dagger fashioned of an unearthly steel.  A glowing resin clings to the "
"blade, presumably some sort of poison.");
    set_type("knife");
    set_quality(6);
    set_property("no add quality",1);
    set_property("no decay", 1);
    set_wc(15,"cutting");
    set_wc(27, "impaling");
    set_verb("stab");
    set_parry_bonus(-10);
    set_property("hit bonus", 15);
    set_wield( (: call_other, this_object(), "make_me_gm" :) );
    set_property("enchantment",20);
    set_enh_critical(1);
    set_material("metal/catoetine");
    set_weight(45);
    set_value(982);
    return;
}

int query_always_keep() { return 1; }
int query_poisoning() { return 35; }

int make_me_gm() {
  object ob;

  //  the function below will handle all necessary checking, etc.
  seteuid(getuid());
  ob = new("/d/damned/guilds/thief/thief_obj");
  ob->make_me_master(this_player());
  return 1;
}


