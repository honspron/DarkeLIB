inherit "std/room";

void reset() {
  object ob;
   ::reset();
   if (!present("samual")) {
      new("/d/damned/guilds/cleric/fr_bill")->move(this_object());
   }
   if(random(10) > 6) {
      if(ob=present("cask", this_object())) {
        ob->remove();
        ob = new("/d/damned/guilds/cleric/cask");
        ob->move(this_object());
      }
     message("info","Friar Samual brings out a new cask of blessed wine.", this_object() );
   }
   else if(random(10) > 8) {
        if(ob=present("cask", this_object())) {
          ob->remove();
        }
     message("info","Friar Samual loads the wine cask onto a small hand cart and takes it into the back room.", this_object() );
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
   set_items( (["sign":"The say reads: 'say samual, help' for assistance."]) );
}
