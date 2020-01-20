#include <move.h>

#include <std.h>



inherit "/std/armour";

inherit AUTOLOAD;



void create() {

  int x;

  ::create();

  set("id", ({ "robe", }));

  set_name("robe");

  set("short", "Robe of the Enlightened Order");

  set("long",@TEXT

This is a garment of the finest silk and satin.  It is predominantly

sky blue with saphire satin trim.  Centered on the back panel is the

symbol of "the great eye."

TEXT

);

  set_limbs(({"right arm", "left arm", "torso", "right leg", "left leg"}));

  set_weight(150);



  set_ac(35);

  x = random(10);

  switch(x) {

    case 0: set_ac(50, "fire"); break;

    case 1: set_ac(50, "cold"); break;

    case 2: set_ac(50, "electricity"); break;

    case 3: set_ac(50, "aether"); break;

    case 4: set_ac(50, "holy"); break;

    case 5: set_ac(50, "disruption"); break;

    case 6: set_ac(50, "plasma"); break;

    case 7: set_ac(50, "vacuum"); break;

    case 8: set_ac(50, "infernal"); break;

    case 9: set_ac(50, "acid"); break;

  }

  set_wear((: call_other,this_object(), "wear_me" :));

  set_enh_critical(-1);

  set_value(42000);

  return;

}



int query_always_keep() { return 1; }



int wear_me() {

  object ob;

  int x;

  string cl, gm, nam;

  

  seteuid(getuid());

  x = this_player()->query_level();

  cl = this_player()->query_class();

  gm = "/d/damned/guilds/join_rooms/seer_join"->query_master();

  nam = this_player()->query_true_name();

  if((string)this_player()->query_name() != "guildmaster")

  if(cl != "seer" || nam != gm) {

    write(@TEXT%^MAGENTA%^

In your attempt to wear the robe, you become aware of the

fact that you have not been inducted into the Enlightened

Order...the robe constricts and contorts and you fail to

properly wear the garment.  You should feel fortunate that

it did not kill you.

TEXT

);

    return;

  }

  write("You feel the warmth and comfort of your robe.");

  return 1;

}

