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
   add_exit("/d/damned/guilds/thief/train_room", "north");
   add_exit("/d/damned/guilds/thief/shop_store", "west");
   set_door("iron door", "/d/damned/guilds/thief/shop_store", "west",
	    "thief store key");
   set_open("iron door", 0);
   set_locked("iron door", 1);
   set_lock_level("iron door", 22);
   set("short","The Thieves Shop");
   set("long",
"This small, dark shop sells the various tools which thieves use to "
"practice their trade.  Dai Blackthorn, the shopkeeper, is always eager "
"to help out his fellow thieves by selling them equipment.");
 
   seteuid(getuid());
   set_items( (["sign":"The sign reads: 'say dai, help' for assistance."]) );
}
 
