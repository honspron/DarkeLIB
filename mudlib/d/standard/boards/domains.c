inherit "/std/room";

void create() {
    object ob;

    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "The Planning Room");
    set("long", (: this_object(), "go_away" :));
    ob = new("/std/bboard");
    set_exits(
	([ "main" : "/d/standard/adv_inner" ]) );
    ob->set_name("board");
   ob->set_id( ({ "board", "Domain theme board" }) );
    ob->set_board_id("domains");
    ob->set_max_posts(30);
    ob->set_location("/d/standard/boards/domains");
    ob->set("short", "the Domain Themes Board");
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

