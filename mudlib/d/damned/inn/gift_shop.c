
inherit "std/room";

void reset() {
   ::reset();
   if (!present("fred")) {
      new("/d/damned/inn/fred")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("/d/damned/inn/main_room", "west");
   set("short","Fred's gift shop");
   set("long","Welcome to the Blue Dragon gift shop!  There are not "+
       "many gifts here, but the few that are look quite valuable.");
   set_items( (["sign":"The say reads: 'say shopkeeper, help' for assistance."]) );
}

int clean_up() {
  if(find_player("diewarzau"))
    tell_object(find_player("diewarzau"), "%^RED%^Gift shop is clean. "+
	base_name(this_object()));
  return ::clean_up();
}
