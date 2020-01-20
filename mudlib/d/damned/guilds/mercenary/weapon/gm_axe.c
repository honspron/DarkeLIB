//      Edited by Tailwind

//

//      Blessed ReturnLIB

//      Tailwind 10/28/98



#include <std.h>

#include <../merc.h>


inherit "/std/weapon";

inherit AUTOLOAD;


create() {

    ::create();

    set_ac(20);

    set("id", ({ "axe", "guildmaster axe", "blur" }));

    set_name("blur");

    set("short", "Blur, the Axe of the Guildmaster");

    set("long", "Blur has a long and brutal history behind it. The tinker who originally forged it was killed for this blade by an unscrupulous customer. It was then passed on from generation to generation, until it became the sign of the guildmaster of the Mercenaries. Now, it is fought for extensively. It appears you have won it. The Axe is renowned for its exceptional speed and cutting power." );

    set_type("axe");

    set_quality(6);

    set_property("no decay",1);

    set_property("no add quality",1);

    set_wc(30, "cutting");

    set_wc(30, "crushing");

    set_wc(30, "speed");

    set_wc(30, "paralysis");

    set_verb("cleave");

    set_parry_bonus(30);

    set_wield( (: call_other, this_object(), "make_me_gm" :) );

    set_property("enchantment",20);

    set_enh_critical(2);

    set_weight(200);

    set_value(60000);

    return;

}



int query_always_keep() { return 1; }

int make_me_gm() {

  object ob;



  //  the function below will handle all necessary checking, etc.

  seteuid(getuid());

  ob = new(OBJ+"merc_obj");

  ob->make_me_master(this_player());

  return 1;

}
