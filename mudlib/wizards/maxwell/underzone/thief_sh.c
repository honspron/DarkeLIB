#include "/adm/include/std.h"
#include "under.h"
inherit "/std/vault";
 
void reset() {
   ::reset();
   if (!present("dai")) {
      new("/d/damned/guilds/thief/dai_blackthorn")->move(this_object());
   }
}
 
void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",1);
   add_exit(GUILDR+"thief_jo", "south");
   set_door("iron door", "/d/damned/guilds/thief/shop_store", "west",
	    "thief store key");
   set_open("iron door", 0);
   set_locked("iron door", 1);
   set_lock_level("iron door", 22);
   set("short","The Thieves Shop");
   set("long",
"You are standing in a small stone chamber. Against one wall is a "
"small wooden altar. This must have been a prayer room when the temple "
"had regular visitors. The shadows are very dark here and you can feel "
"the presence of others around you.\nThere is a small wooden sign nailed "
"to the wall here.\n");
   seteuid(getuid());
   set_items( (["sign":"The sign reads has a message scrawled on it "
                "in blood red ink. Maybe you can read it."]) );
}
init() {
  ::init();
  add_action("read_sign","read");
}
int read_sign(string str){
   if(!str){
    write("Read what?");
    return 1;
   }
   if(str == "sign" || str == "message"){
     write("You concentrate on reading the sign. It appears to say\n\n"
"   'Beware you have entered the territory of Dai Blackthorn!\n"
"    if I'm here and you wish to trade in goods or equipment,\n"
"    just 'ask dia, help' and maybe I'll waste some time\n"
"    talking to you.'\n");
     say(this_player()->query_cap_name()+" reads the small wooden sign.");
     return 1;
   }
} 
