#include <std.h>



inherit MONSTER;



create() {

  object ob;

  

  ::create();

  set_name("falstaf");

  set_id( ({ "guard", "treas_guard", "captain" }) );

  set_short("Falstaf, Captain of the Guard");

  set("race", "high-man");

  set_long(@TEXT

Captain Falstaf appears to be on duty to guard and protect the

property and belongings of the Order of Seers.  He not only

verifies the credentials of those that enter but wards against

passage to the top most level of the Seer Tower.

TEXT

);

    set_body_type("human");

    set_level(30);

    set_overall_ac(50);

    ob = new("/d/damned/guilds/seer/items/claymore");

    ob->move(this_object());

    force_me("wield claymore in right hand and left hand");

    ob = new("/d/damned/guilds/seer/items/captain-plate");

    ob->move(this_object());

    force_me("wear plate");    

}



void init() {

  ::init();

  add_action("block_exit", "up");

  add_action("block_exit", "down");

  return;

}



int block_exit() {

  int gld;

  string p_name;

  object join_room, *inv;



  if(wizardp(this_player())) return 0;

   if((string)this_player()->query_class() != "seer") {

     write(@TEXT

Captain Falstaf's voice echos in your mind,  "I can only permit

members of the Order of Seers to pass to or from this room.  You

may leave only over my dead body!"

TEXT

);

    return 1;

  }

  return 0;

}



void die(object ob) {

  "/daemon/chat"->send_chat("seer","Captain Falstaf",

    capitalize(ob->query_true_name())+

    " killed me...the Treasury is now unguarded!");

  ::die(ob);

  return;

}

