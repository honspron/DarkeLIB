inherit "std/room";



void reset() {

   ::reset();

   if (!present("biff")) {

      new("/wizards/diewarzau/obj/mon/biff")->move(this_object());

   }

}



void create() {

   ::create();

   set_property("indoors",1);

   set_property("light",3);

   add_exit("/d/standard/square", "west");

   set("short","Fred's gift shop");

   set("long",

"Weapons adorn the walls of this armoury.  There is a sign on the wall "

"behind the shopkeeper.");

   set_items( (["sign":"The say reads: 'say shopkeeper, help' for"+

	     " assistance."]) );

}

