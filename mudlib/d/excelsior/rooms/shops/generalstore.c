// /wizards/excelsior/rooms/shops/generalstore
// magrunk's store

inherit "std/room";

void reset() {
   ::reset();
   if (!present("magrunk")) {
      new("/wizards/excelsior/rooms/shops/magrunk")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   set("short","Magrunk's");
   set_property("no attack", 1);
   set("long","Welcome to Magrunk's! This is THE center of trading "+
      "here in the city of New Faerie Dust. Magrunk will be perfectly "+
      "happy to buy anything you want to sell him, and sells everything "+
      "he buys at a very reasonable price. This store is open 24 hours a "+
      "day and is very brightly lit, especially in comparison to the dark "+
      "streets outside.  To the south, you can see an intersection.");
   set_items( (["sign":"The say reads: 'say shopkeeper, help' for assistance.","intersection":"To your south."]) );
   set_exits( (["south":"/wizards/excelsior/rooms/inter2"]) );
}
