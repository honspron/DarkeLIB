inherit "std/room";

int chamber();
int read(string str);

void create() {
  ::create();
    set_property("light",3);
    set_property("night light", 3);
    set_property("no scry",1);
    add_exit("/d/damned/akkad/ak_center", "out");
    set("short","Justice Tower Common Room");
    set("long","This is Justice Tower.  It is here that the Council of "+
    "Guildmasters meet to set the Law of the Land and mete out punishment. "+
    "This room is immaculate yet empty, containing only two signs. "+
    "The longer one reads 'Law' and the much more brief one, 'Warrants'. "+
    "You do not notice any other exit besides the one you came in.\n");
}

void init() {
   ::init();
   add_action("chamber","chamber");
   add_action("read","read");
}

int chamber() {
   string gm;
   if(this_player()->query_class())
      gm = "/d/damned/guilds/join_rooms/"+(string)this_player()->query_class()+"_join.c";
   if(!gm || (gm->query_master() != this_player()->query_name()) )
   return notify_fail("Only members of the Council may ascend into the chamber.\n");
   if(!this_player()->query_invis()) {
   message("info",this_player()->query_cap_name()+" begins to glow brightly "+
      "and is gone when the glow fades.",this_object());
   message("info",this_player()->query_cap_name()+" shimmers into existance.",
      find_object("/d/damned/akkad/ak_chamber.c"));
   }
   message("info","You are transported to the Council Chambers.",this_player());
   this_player()->move("/d/damned/akkad/ak_chamber");
   return 1;
}

int read (string str) {
   if(str == "law") {
      message("info","The Law is being written.",this_player());
      return 1;
   }
   else if(str == "warrants") {
      message("info","There are no warrants outstanding.",this_player());
      return 1;
   }
   return 0;
}

