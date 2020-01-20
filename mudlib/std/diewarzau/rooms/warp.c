inherit "/std/room";



void reset() {

  int i;

  ::reset();

  seteuid(getuid());

  if (!present("creature")) {

     i = 4;

     while(i--)

       new("/std/diewarzau/obj/mon/warp_creature")->move(this_object());
  }

}



void create() {

   ::create();

   set_property("indoors",1);

   set_property("light",3);

   set_property("no scry",1);
   set_property("no cast",1);
   set_property("no summon",1);
   set_property("no transport",1);
   set("short","The Warp");

   set("long",

"This is the warp.  It is vast and populated with objects of "

"wonder and danger.");

}



