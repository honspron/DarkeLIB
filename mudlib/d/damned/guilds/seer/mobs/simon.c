#include <std.h>

#define SEER_POOL "/d/damned/guilds/seer/seer_pool" 

inherit MONSTER;

 

mapping warn;



create() {

  ::create();

    warn = ([]);

    set_name("simon");

    set_id( ({"simon", "apprentice", }) );

    set_short("Kantas, the Seer Apprentice");

    set("race", "high-man");

    set_long(@TEXT

TEXT

);

    set_gender("male");

    set_body_type("human");

    set_level(10);

    set_property("handedness", "right hand");

    new("/d/damned/virtual/quarter-staff_5.weapon")->

      move(this_object());

    force_me("wield staff in right hand and left hand");

}



void init() {

  ::init();

  add_action("block_exit", "stairway");

  return;

}





int block_exit() {

  int silv;

  string p_name;

  object join_room, *inv;

 

  if(wizardp(this_player())) return 0;

  if((string)this_player()->query_class() != "seer") {

    write(@TEXT

Simon says in Common: Only residents of the spire are allowed

beyond this point...I'm sorry but I must politely ask you not

to try to ascend the staircase.

TEXT

);

    return 1;

  }

  silv = 5 * (int)this_player()->query_level();

  if((int)this_player()->query_mp() < silv) {

    write(@TEXT

Simon says in Common: Perhaps you should sit and rest some.

Passing the wards can be stressful.

TEXT

);

    return 1;

  }

  write(@TEXT%^MAGENTA%^

You are aware of the ward over the stairway as you pass through it.

TEXT

);

  this_player()->add_mp(-1*silv);

  SEER_POOL->add_mp("guild", this_player()->query_true_name(), silv);

  this_object()->add_hp(silv/10);

  return 0;

}



int can_exceed_max_hp() { return 1; }

