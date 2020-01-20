#include <config.h>

inherit "/std/room";

void create() {
    object ob;
    
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The Hall of the Immortals");
    set("long",
	"This is the meeting green room of the immortals of Nightmare. "
	"In this room, matters of mud policy and events are discussed "
	"by all Nightmare immortals so that everyone might know what "
	"is going on.  There is a room for discussing LPC south and "
	"a planning room east where immortals post their plans for areas "
	"domains, guilds, and quests.");
    set_exits( 
	      (["up" : "/d/standard/mudlib",
		"north" : "/d/standard/adv_main",
		"south" : "/d/standard/lpc_inner",
		"east" : "/d/standard/planning_room"]) );

    ob = new("std/bboard");
    ob->set_name("board");
    ob->set_id( ({ "board", "reality board" }) );
    ob->set_board_id("immortal");
    ob->set_max_posts(30);
    ob->set_location("d/standard/adv_inner");
    ob->set("short", "Immortal's Reality Board");
    ob->set("long", "Posts any notes concerning the mud which do "
	    "not belong out in a public forum among players "
	    "here for immortal discussion.\n");
    set_property("no steal", 1);
}

int receive_objects() {
  if(!previous_object()->is_player())
    return 1;
  if(!wizardp(previous_object())) {
    message("my_action", "You cannot penetrate the force of "
	    "the blue force shield.", this_player());
    return 0;
  }
  return 1;
}

