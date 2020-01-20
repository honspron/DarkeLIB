inherit "/std/room";

void create() {
  object ob;
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "seer_board"}) );
  ob->set_board_id("seer_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/seer/rooms/main_room");
  ob->set("short","Board of the Order");
  ob->set("long","A message board for players to post notes.\n");
  set("short", "Main Hall of the Seer's Tower");
  set("long", @TEXT 
TEXT
);

  set_property("light", 3);
  set_property("indoors", 1);
  
  set_exits( ([
    "up"    : "/d/damned/guilds/seer/rooms/meditate",
    "down"  : "/d/damned/guilds/join_rooms/seer_join",
             ]));
  
  return;
}

void reset() {
  if(!present("kantas"))
    new("/d/damned/guilds/seer/mobs/kantas")->move(this_object());
  return;
}
