/*

 * Clan guards, basic.

 *

 */



#include <daemons.h>



inherit "/std/monster.c";



string clan_name;



void create() {

  object ob;

  

  ::create();

    set_name("guard");

    set_id( ({ "guard" }) );

    set_short("A guard");

    set("race", "high-man");

    set_languages(({ "common", "middle-english" }));

    set_long(

    "An imposing fellow indeed, this muscular high-man looks very capable of guarding "

    "the stronghold against would-be encroachers.");

    set_body_type("human");

    set_level(16);

    set_property("melee damage", ([ "crushing" : 20]));

    set_skill("melee", 85);

    set_skill("dodge", 78);

    set_skill("parry", 80);

    set_stats("dexterity", 105);

    set_stats("strength", 121);

    set_skill("resist stun", 67);

    set_skill("two handed polearm", 111);

    set_property("enhance criticals", -2);

    set_overall_ac(30);

    ob = new("/d/damned/virtual/halberd_6.weapon");

    switch(random(4)) {

    case 0:

      ob->set_material("metal/mithril");

      break;

    case 1:

      ob->set_material("metal/iysaughton");

      break;

    case 2:

      ob->set_material("metal/raysorite");

      break;

    case 3:

      ob->set_material("metal/elrodnite");

      break;

    }

    set_languages(({ "common" }));

    ob->set_property("enchantment", 8);

    ob->set_property("brittle", 90);

    ob->set_property("hit bonus", 20);

    ob->move(this_object());

    force_me("wield halberd in right hand and left hand");

    ob = new("/d/damned/virtual/breast-plate.armour");

    ob->set_property("enchantment", 13);

    ob->move(this_object());

    force_me("wear plate");

    ob = new("/d/damned/virtual/great-helm.armour");

    ob->set_property("enchantment", 15);

    ob->move(this_object());

    force_me("wear helm");

    ob = new("/d/damned/virtual/iron-greaves.armour");

    ob->set_property("enchantment", 15);

    ob->move(this_object());

    force_me("wear greaves");

    ob = new("/d/damned/virtual/iron-bracer.armour");

    ob->set_property("enchantment", 15);

    ob->move(this_object());

    ob = new("/d/damned/virtual/iron-bracer.armour");

    ob->set_property("enchantment", 15);

    ob->move(this_object());

    force_me("wear bracer on left arm");

    force_me("wear bracer 2 on right arm");

    set("aggressive", (: call_other, this_object(), "check_clan" :));

    set_max_hp(2000);

    set_hp(2000);

    set_exp(1000);

}



void init() {

  ::init();

  add_action("block_exit", "hall");

  return;

}



int block_exit(string null) {

  if(!clan_name) return 0;

  if(this_player()->query_invis()) return 0;

  if(skill_contest((int)this_object()->query_skill("perception"),

      (int)this_player()->query_stealth(), 1) != 1) return 0;

  if(clan_name == (string)this_player()->query_guild()) {

    write("The guard lets you pass.");

    return 0;

  }

  if(this_player()->is_pet() && this_player()->query_owner() &&

    CLAN_D->clan_member((string)this_player()->query_owner(),

    clan_name)) return 0;

  write("The guard bars your way.");

  message("info", "The guard bars "+(string)this_player()->query_cap_name()+

    " from intering the clan hall.", environment(), ({ this_player() }));

  return 1;

}



int check_clan(object who) {

  if(!clan_name) return 0;

  if(!who->is_player() && !who->is_pet()) return 0;

  if(wizardp(who)) {

    message("info", "The guard bows to you.", who);

    return 0;

  }

  if(who->is_pet() && who->query_owner() && CLAN_D->clan_member((string)who->query_owner(),

    clan_name)) return 0;

  if(who->query_guild() != clan_name) {

    message("info", "The guard yells out: Death to the enemies of Clan "+

            capitalize(clan_name)+"!!!", environment());

    return 1;

  }

  if(!random(3) && who->is_player()) {

    force_me("speak common");

    force_me("say Hello ho ho, milord "+(string)this_player()->query_cap_name()+".");

  }

  return 0;

}



void setup(string cname) {

  clan_name = cname;

  set_short("A guard of Clan "+capitalize(cname));

  set_id(({ "guard", "guard of clan "+cname, "guard of "+cname }));

}



  

