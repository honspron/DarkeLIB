/*

 * Clan guards, not-so-basic.

 *

 */



#include <daemons.h>



inherit "/std/monster.c";



string clan_name;



void create() {

  object ob;

  

  ::create();

    set_name("knight");

    set_id( ({ "knight" }) );

    set_short("A knight");

    set("race", "high-man");

    set_languages(({ "common", "middle-english" }));

    set_long(

    "This stately fighter is clad in shining metal from head to toe.  "

    "He wields his sword with prowess.");

    set_gender("male");

    set_body_type("human");

    set_level(18);

    set_property("melee damage", ([ "crushing" : 20]));

    set_skill("melee", 85);

    set_skill("dodge", 88);

    set_skill("parry", 105);

    set_skill("block", 105);

    set_stats("dexterity", 115);

    set_stats("strength", 131);

    set_skill("resist stun", 87);

    set_skill("blade", 130);

    set_property("enhance criticals", -2);

    set_overall_ac(40);

    set_skill("conjuration", 70);

    set_spell_level("ice dagger", 6);

    set_mp(2000);

    add_spell("ice dagger", "$A");

    set_skill("magery", 70);

    set_spell_level("power word, stun", 6);

    add_spell("power word, stun", "$A");

    ob = new("/d/damned/virtual/broad-sword_6.weapon");

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

    ob->set_property("enchantment", 15);

    ob->set_property("brittle", 95);

    ob->set_property("hit bonus", 25);

    ob->set_wc(6, "fire");

    ob->move(this_object());

    ob->set_property("no steal", 1);

    force_me("wield sword in right hand");

    ob = new("/d/damned/virtual/breast-plate.armour");

    ob->set_property("enchantment", 18);

    ob->set_property("brittle", 50);

    ob->move(this_object());

    ob->set_property("no steal", 1);

    force_me("wear plate");

    ob = new("/d/damned/virtual/great-helm.armour");

    ob->set_property("enchantment", 20);

    ob->set_property("brittle", 50);

    ob->move(this_object());

    ob->set_property("no steal", 1);

    force_me("wear helm");

    ob = new("/d/damned/virtual/iron-greaves.armour");

    ob->set_property("enchantment", 20);

    ob->set_property("brittle", 50);

    ob->move(this_object());

    ob->set_property("no steal", 1);

    force_me("wear greaves");

    ob = new("/d/damned/virtual/iron-bracer.armour");

    ob->set_property("enchantment", 20);

    ob->set_property("brittle", 50);

    ob->move(this_object());

    ob->set_property("no steal", 1);

    ob = new("/d/damned/virtual/iron-bracer.armour");

    ob->set_property("enchantment", 20);

    ob->set_property("brittle", 50);

    ob->move(this_object());

    ob->set_property("no steal", 1);

    force_me("wear bracer on left arm");

    force_me("wear bracer 2 on right arm");

    ob = new("/d/damned/virtual/large-shield.armour");

    ob->set_material("metal/laen");

    ob->set_property("enchantment", 20);

    ob->set_property("brittle", 50);

    ob->set_property("no steal", 1);

    ob->move(this_object());

    force_me("wear shield on left hand");

    set("aggressive", (: call_other, this_object(), "check_clan" :));

    set_die((: call_other, this_object(), "pre_death" :));

    set_max_hp(4000);

    set_hp(4000);

    set_exp(1000);

}



int pre_death(object null) {

   message("info", "%^GREEN%^%^BOLD%^Before the knight's death, a dwarf appears to "

    "scavenge his equipment so it may be used for the one who takes his place.",

    environment());

   map_array(all_inventory(this_object()), (: call_other :), "remove");

   set_die(0);

   return 1;

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

  if(this_player()->is_pet() && this_player()->query_owner() &&

    CLAN_D->clan_member((string)this_player()->query_owner(),

    clan_name)) return 0;

  if(clan_name == (string)this_player()->query_guild()) {

    write("The guard lets you pass.");

    return 0;

  }

  write("The guard bars your way.");

  message("info", "The guard bars "+(string)this_player()->query_cap_name()+

    " from intering the clan hall.", environment(), ({ this_player() }));

  return 1;

}



int check_clan(object who) {

  int i, max;

  object room;

  

  if(!clan_name) return 0;

  if(!who->is_player() && !who->is_pet()) return 0;

  if(wizardp(who)) {

    message("info", "The guard bows to you.", who);

    return 0;

  }

  if(who->is_pet() && who->query_owner() && CLAN_D->clan_member((string)who->query_owner(),

    clan_name)) return 0;

  if(who->query_guild() != clan_name) {

    max = (int)CLAN_D->query_num_rooms(clan_name);

    for(i=1; i<=max; i++) {

      if(catch(room=load_object(sprintf("/d/damned/virtual/%s_hall_%d.clan_strong",

                clan_name, i)))) continue;

      if(!room) continue;

      message("info", "A Knight of your clan yells from the courtyard: My liege!!! "

          "We are under attack by the knave "+(string)who->query_cap_name()+"!",

          room);

    }

    message("info", "The knight yells out: Base villain! Prepare to meet thy doom!", environment());

    return 1;

  }

  if(!random(3) && who->is_player()) {

    force_me("speak common");

    force_me("say Greetings, lord "+(string)this_player()->query_cap_name()+".");

  }

  return 0;

}



void setup(string cname) {

  clan_name = cname;

  set_short("A Knight of Clan "+capitalize(cname));

  set_id(({ "knight", "knight of clan "+cname, "knight of "+cname }));

}



  

