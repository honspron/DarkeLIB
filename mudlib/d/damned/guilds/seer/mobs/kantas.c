#include <std.h>

#define SEER_POOL "/d/damned/guilds/seer/seer_pool_d" 

inherit MONSTER;

 

mapping warn;



create() {

  ::create();

    warn = ([]);

    set_name("kantas");

    set_id( ({"guard", "kantas", "sergeant", }) );

    set_short("Kantas, the Sergeant of the Guard");

    set("race", "high-man");

    set_long(@TEXT

Sergeant Kantas stands quietly before you with his hands behind

him.  While he appears distant and aloof, you suspect he is aware

of your presence.

TEXT

);

    set_body_type("human");

    set_level(18);

    set_exp(20000);

    set_property("handedness", "right hand");

    new("/d/damned/virtual/long-sword_5.weapon")->

      move(this_object());

    new("/d/damned/virtual/large-shield.armour")->

      move(this_object());

    new("/d/damned/virtual/chain-vest.armour")->

      move(this_object());

    new("/d/damned/virtual/iron-greaves.armour")->

      move(this_object());

    new("/d/damned/virtual/iron-bracer.armour")->

      move(this_object());

    new("/d/damned/virtual/iron-bracer.armour")->

      move(this_object());

    force_me("wear vest");

    force_me("wield sword in right hand");

    force_me("wear shield on left hand");

    force_me("wear greaves");

    force_me("wear bracer 2 on right arm");

    force_me("wear bracer on left arm");

}

 

void init() {

  ::init();

  add_action("block_exit", "up");

  add_action("block_board", "read");

  add_action("block_board", "look");

  add_action("block_board", "post");

  return;

}





int block_exit() {

  int silv;

  string p_name;

  object join_room, *inv;

 

  if(wizardp(this_player())) return 0;

  if((string)this_player()->query_class() != "seer") {

    write(@TEXT

You hear Sergeant Kantas' voice in your mind:  Only residents of

the tower are allowed beyond this point...I'm sorry but I must

politely ask you not to ascend any further.

TEXT

);

    return 1;

  }

  silv = 5 * (int)this_player()->query_level();

  if((int)this_player()->query_mp() < silv) {

    write(@TEXT

You hear Sergeant Kantas' voice in your mind:  Relax a moment and

perhaps you will have enough mental stamina to push through the

mind barrier.

TEXT

);

    return 1;

  }

  write(@TEXT%^MAGENTA%^

You steel your will and press through the mind barrier that wards

the archway leading to the staircase upward.

TEXT

);

  this_player()->add_mp(-1*silv);

  SEER_POOL->add_mp("guild", this_player()->query_true_name(), silv);

  this_object()->add_hp(silv);

  return 0;

}



int can_exceed_max_hp() { return 1; }



int block_board(string str) {

  string nam;



  if(!str) return 0;

  if(str == "board" || str == "at board") {  

  if((string)this_player()->query_class() == "seer") { return 0; }

  nam = this_player()->query_true_name();

  if(!warn[nam]) {

    write(@TEXT

You hear the voice of Sergeant Kantas in your mind, "This board is

reserved for the exclusive use of the residents of this tower."



After a pause the voice continues, "You are not permitted use or

access its contents! Consider yourself warned."

TEXT

);

    warn[nam] = 1;

    return 1;

  }

  else switch(warn[nam]) {

    case 1:  write(@TEXT

You hear the voice of Sergeant Kantas in your mind, "Perhaps you

did not understand me.  This board is for the exclusive use of

the residents of this town...None others...this means you!  Please

do not try my patience."

TEXT

);

      warn[nam]++;

      return 1;

    case 2:  write(@TEXT

You hear the voice of Sergeant Kantas in your mind, "Are you daft,

stupid, or just a plain simpleton?  I have warned you twice now,

not to attempt to use or access the Seers' Board.  Last warning...

DO NOT attempt to use the board lest I be forced to take action!"

TEXT

);

      warn[nam]++;

      return 1;

    case 3:  write(@TEXT

You hear the voice of Sergeant Kantas in your mind, "Very well,

you leave me no alternative but to expell you from the tower."



The guard reaches inside his waistcoat and draws out a glowing

crystal...and your environment disolves...

TEXT

);

      warn[nam]++;

      this_player()->move("/d/standard/square");

      return 1;

    default:  write(@TEXT

You hear the voice of Sergeant Kantas in your mind, "You have

left me with no alternative...



The guard reaches inside his waistcoat and draws out a pitch

black figurine and speaks your name to it...he then throws it

to the ground and even as it shatters, a black misty cloud

completely surrounds you.

TEXT

);

      warn[nam]++;

      "/daemon/chat"->send_chat("seer","Sergeant Kantas",

        "I was forced to kill "+capitalize(this_player()->query_true_name())+

        " for attempting to access the Seer's Message Board.");

      this_player()->die();

      return 1;

  }

  }

  return 0;

}



void die(object ob) {

  "/daemon/chat"->send_chat("seer","Sergeant Kantas",

    capitalize(ob->query_true_name())+

    " killed me...the Main Hall is now unguarded!");

  ::die(ob);

  return;

}

