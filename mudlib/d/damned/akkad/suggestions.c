#include <config.h>

inherit "/std/room";

void create() {
    object ob;
    
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The DarkeMUD suggestion board.");
    set("long",
	"This is where players of DarkeMUD can post suggestions for the mud.");
    
    add_exit("/d/standard/post", "west");

    ob = new("std/bboard");
    ob->set_name("board");
    ob->set_id( ({ "board", "suggestion board" }) );
    ob->set_board_id("suggestion");
    ob->set_max_posts(30);
    ob->set_location("d/damned/akkad/suggestions");
    ob->set("short", "Suggestion Board");
    ob->set("long", "Posts any suggestions for the mud here.\n");
    set_property("no steal", 1);
}


