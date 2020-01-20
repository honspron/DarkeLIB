//	An example guildmaster for fighters.

//

//	DarkeLIB 0.1

//	Diewarzau 8/8/95

//

//      Edited by Tailwind

//

//      Blessed ReturnLIB

//      Tailwind 10/28/98



#include <../merc.h>



inherit "/std/guilds/npc_guildmaster";



//	He is set up identically to a monster.



void create() {

  object ob;



  ::create();



  //  The one difference is the following line:

  set_join_room(ROOMS+"merc_join");

  //  The above refers the guildmaster to the joining room, which

  //  handles all "book keeping"



  set("short", "The Mercenary Guildmaster");

  set("long", "This is an arrogant young man, few in years, but somewhat better than most in experience. He is the veteran of many campaigns already, and wants to live for many more. He has bulging muscles, and looks to be no push-over.");

  set_level(25);

   set_max_hp(6000);

   set_hp(6000);

   set_overall_ac(75);

  set_property("base hp regen", 80);

  set_gender("male");

  set("race", "human");

  set_body_type("human");

  set_id(({ "guildmaster", "mercenary", "mercenary guildmaster" }));

  //  NOTE:  It is important that, if you set_id, you include

  //  "guildmaster" as one of them.  If you do not set_id, he

  //  will still work.

  set_name("guildmaster");

  set_property("melee damage", ([ "crushing" : 20 ]));

  set_skill("melee", 80);

  set_skill("perception", 200);

  set_skill("dodge", 160);

  set_skill("shield bash", 120);

  set_skill("whirlwind attack", 120);

  set_skill("resist stun", 100);

  set_skill("focused attack", 65);

  set_skill("reverse stroke", 200);

  set_skill("parry", 150);

  set_skill("two handed blade", 250);

new(WEAP+"gm_axe.c")->move(this_object());

force_me("wield axe in right hand");

  set_stats("strength", 200);

  set_skill("attack", 200);

  return;

}



int query_num_rounds() { return 3; }