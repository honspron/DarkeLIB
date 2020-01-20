#include <std.h>



inherit MONSTER;



create() {

  object ob;

  

  ::create();

  set_name("guard");

  set_id( ({ "guard", "shadow guard", "shadow" }) );

  set_body_type("human");

  set_level(30);

  set_overall_ac(50);

  set_property("melee damage", ([ "psychic" : 50, ]));

}



void init() {

  ::init();

  add_action("block_exit", "up");

  add_action("block_exit", "down");



  set_short(this_player()->query_short());

  set_long(this_player()->query_name()+" "+this_player()->query_description());

  set("race", this_player()->query_race());

  set_id( ({ "guard", "shadow guard", "shadow" })+({ this_player()->query_name() }) );

  set_name(this_player()->query_name());

  set_emotes(5, ({

      this_player()->query_cap_name()+" peers at you.",

      this_player()->query_cap_name()+" says in Common:  I know you're here.",

      this_player()->query_cap_name()+" ponders the situation.",

      this_player()->query_cap_name()+" points at you.",

    }), 0);

  set_achats(15, ({

      this_player()->query_cap_name()+" says in Common: Help me...!!!",

      "%^CYAN%^You sense the aura of a skill steal spell.\n"+

      this_player()->query_cap_name()+" begins casting a spell.",

      "%^CYAN%^"+this_player()->query_cap_name()+" casts a spell.%^RESET%^\n"+

      this_player()->query_cap_name()+" casts a true channel spell and is now supported by the whole guild.",

    }) );

  return;

}



int block_exit() {

  int gld;

  string p_name;

  object join_room, *inv;



  if(wizardp(this_player())) return 0;

  if(this_player()->query_ghost()) return 0;

   if((string)this_player()->query_class() != "seer") {

     write(this_player()->query_cap_name()+" says in Common:  "+

"I can only permit members of the Order of Seers to pass to or "+

"from this room.  You may leave only over our dead body!"

);

    return 1;

  }

  return 0;

}



void die(object ob) {

  "/daemon/chat"->send_chat("seer","Shadow Guard",

    capitalize(ob->query_true_name())+

    " killed me...the Meditation Chamber is now unguarded!");

  ::die(ob);

  return;

}

