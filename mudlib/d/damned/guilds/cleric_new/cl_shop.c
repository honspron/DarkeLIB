inherit "std/room";

void reset() {
   ::reset();
   if (!present("bill")) {
      new("/d/damned/guilds/cleric/fr_bill")->move(this_object());
   }
}

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("/d/damned/guilds/cleric/confess", "north");
   set("short","Guiding Lumenance");
   set("long", @TEXT
You have entered the Guiding Lumenance.  The Holy Church sponsors this
humble store.  Here you can be obtain many items of a religious or
spiritual nature.  There is a sign on the side wall.
TEXT
);
   seteuid(getuid());
   new("/d/damned/guilds/cleric/cask")->move(this_object());
   set_items( (["sign":"The say reads: 'say bill, help' for assistance."]) );
}

