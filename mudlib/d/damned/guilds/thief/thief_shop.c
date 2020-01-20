#include <under.h>
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
    set_property("no attack", 1);
    set_property("no steal", 1);
    set_property("no castle", 1);
    set_property("no spell", 1);
   add_exit(UNTHIEF+"thief5", "south");
   add_exit("/d/damned/guilds/thief/shop_store","west");
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
"to the wall here.\n"
"There is a list of some kind nailed to the wall here.\n");
   seteuid(getuid());
   set_items( (["sign":"The sign has a message scrawled on it "
                "in blood red paint. Maybe you can read it.",
                "list":"It would appear to be a list of plants.  Perhaps you should read it."]) );
}
void init() {
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
"    If I'm here and you wish to trade in goods or equipment,\n"
"    just ask me for help and maybe I'll waste some time talking\n"
"    to you.'\n");
     say(this_player()->query_cap_name()+" reads the small wooden sign.");
     return 1;
   }
   if(str == "list") {
write("\nRumor has it that the following plants may be used to create poisons:\n"
"\n"
"Blood Root, Demon Horns, Draco Thorns, Durdin Seeds, Faerie Blossoms,\n"
"Fulma Leaves, Gangus Root, Geckin Twigs, Jerup Weeds, Jumbu Sprouts,\n"
"Koji Mushrooms, Lotus Blossoms, Marsig Mushrooms, Nagasik Leaves,\n"
"Pine Needles, Pixie Winks, Polkin Buds, Purple Grass, Yellow Grass,\n"
"and Yithki Weeds.\n"
"\n"
"Certain roots and thorns are said to be especially toxic, although it\n"
"it unknown as to which plants truly make the best poisons.  Grasses\n"
"and weeds normally contain low levels of toxins.\n"
"\n"
"It is said that certain poisonous plants that cannot be found in the\n"
"plains of this continent are sold by those who deal in magical items.\n"
"But no one knows of any such plants or of any such shopkeepers who have\n"
"these plants.\n");
   say(this_player()->query_cap_name()+" reads the list of plants on the wall.");
   return 1;
   }
} 
