inherit "/std/room";

void create() {
    object ob;

    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The Planning Room");
    set("long", "Post your coding questions here on the LPC and MudOS board.");
    ob = new("/std/bboard");
    set_exits(
        ([ "main": "/d/standard/adv_main"]) );
    ob->set_name("board");
    ob->set_id( ({ "board", "LPC and MudOS board" }) );
    ob->set_board_id("lpc");
    ob->set_max_posts(30);
    ob->set_location("/d/standard/boards/LPC");
    ob->set_short("the LPC and MudOS board");
    ob->set("long", "A board for posting ideas so that others "
	    "will not use them.\n");
}

int do_check() { return archp(this_player()); }

string go_away() {
    string str;

    if(archp(this_player())) str = "The arch meeting room is upstairs. ";
    else str = "";
    str += "All ideas are unclaimed until they appear here.  "
      "If your idea is taken, and you did not post it, you have only yourself to blame.";
    return str;
}

