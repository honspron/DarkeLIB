//	DarkeLIB 0.1 
//      ++Drizzt

inherit "/std/guilds/join_room";

void create() {
  object ob;
  set_class_name("child");
  ::create();
  ob = new("std/bboard");
  ob->set_name("board");
  ob->set_id( ({"board", "newbie_board"}) );
  ob->set_board_id("newbie_board");
  ob->set_max_posts(25);
  ob->set_location("d/damned/guilds/join_rooms/child_join");
  ob->set("short","Newbie Board");
  ob->set("long","A board for players to post notes.\n");
  set("short", "The Newbie Guild");
  set("long", "There is a stairway leading up to the newbie training"+
     " room.  There is also a bright %^YELLOW%^sign%^RESET%^ on the north wall.");
  add_item("sign", "Couple things you do as a newbie:\n"+
   "1) Be sure to check out the webpage at www.shadowlands.com or help newbie.\n"+
   "2) Talk to players for help, not wiz's.\n"+
   "3) Guildmasters can let ya into the guilds so talk to them also.\n"+
"4) Go back to #1\n"+
   "Ohh yea.. You can join a guild at any lvl long as a GM invites you!\n");
  set_property("light", 2);
  set_property("indoors", 1);
 
  set("guildmaster", "/d/damned/guilds/child/child_gm"); 

  add_exit("/d/damned/guilds/child/train_room", "up");
  add_exit("/d/damned/akkad/ak_tavern3", "east");

  this_object()->reset();
  return;
}

void reset() {
  if(!present("guildmaster", this_object()))
   new("/d/damned/guilds/child/child_gm")->move(this_object());

  return;
}

  
