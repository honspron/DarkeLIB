inherit "/std/room";

void create() {
    object ob;

    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The Planning Room");
    set("long", (: this_object(), "go_away" :));
   set("long", "The Lost and the Damned board is the place where all "
               "wizards should post their upcoming areas once their ideas "
              "have been approved by and arch.  And stop screwing around "
"with the room descriptions in this area, damnit!\n-Duridian "
               "\nAnd let us not forget that it is the wizards job to peruse the board to make sure their brilliant idea is not already taken. Am I screwing, Duridian?\n-Excelsior ");
    ob = new("/std/bboard");
    add_exit("/d/standard/adv_main", "hall");
    ob->set_name("board");
    ob->set_id( ({ "board", "Lost and the Damned board" }) );
    ob->set_board_id("damned");
    ob->set_max_posts(100);
    ob->set_location("/d/standard/boards/damned");
    ob->set("short", "the Lost and the Damned Board");
    ob->set("long", "A board for posting ideas so that others "
	    "will not use them.\n");
}

int do_check() { return archp(this_player()); }

string go_away() {
    string str;

    str = "";
    str += "All ideas are unclaimed until they appear here.  "
      "If your idea is taken, and you did not post it, you have only yourself to blame.";
    return str;
}
