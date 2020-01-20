#include <config.h>

inherit "/std/room";

void create() {
    object ob;
    
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The DarkeMUD board.");
    set("long",
    "This is where players of DarkeMUD can post kewl comments for the mud.\n");
    add_exit("/d/standard/post", "east");
    ob = new("std/bboard");
    ob->set_name("board");
    ob->set_id( ({ "board", "comment board", "DarkeMUD", "darke" }) );
    ob->set_board_id("comment");
    ob->set_max_posts(30);
    ob->set_location("d/damned/akkad/comments");
    ob->set("short", "The DarkeMUD is kewl Board");
    ob->set("long", "Posts any kewl comments for the mud here.\n");
    set_property("no steal", 1);
}
