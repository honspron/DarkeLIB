inherit "std/room";

int tower();
int read(string str);

void create() {
   object ob;
  ::create();
    set_property("light",3);
    set_property("night light", 3);
    set_property("no scry",1);
    set_property("no attack",1);
    set_property("no spell",1);
    set_property("vote",1);
    
    set("short","Council Vote Room");
    set("long",@TEXT
TEXT
);
    add_exit("/d/damned/akkad/council_v_room", "vote");
    ob=new("/d/damned/akkad/voteboard");
    ob->set_name("board");
    ob->set_id ( ({"board", "vote board", "vote", }) );
    ob->set_board_id("council_vote");
    ob->set_max_posts(50);
    ob->set_location("/d/damned/akkad/council_v_room");
    ob->set("short", "Council Vote Board");
    ob->set("long", "This board exists for Council members to state a voting issues.\n");
    ob->set_property("vote", 1);
}

void init() {
   ::init();
}
