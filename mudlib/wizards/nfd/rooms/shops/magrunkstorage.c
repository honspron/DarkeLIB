// /d/nfd/rooms/shops/magrunkstorage
// magrunk's stoarage room. NO ACCESS

inherit "std/room";

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",1);
   set_property("storage room",1);
   set("short","Storage- Magrunk's");
	reset();
   set("long","If you are reading this and Excelsior finds out, you are in "+
      "deep shit. Bahahahaha.");
   set_items( (["shit":"Feces or excretement, often used as a profanity.",
            "excelsior":"Mad for you reading this. Grrrr." ]) );
   set_exits( ([]) );
}

void reset() {
	int i;
	i = 5;
	if (!present("torch")) {
	while (i > 0) {
		new("/std/obj/torch")->move( this_object() );
	i--;
	}
}
	if (!present("bag")) {
		i = 5;
		while (i > 0) {
			new("/d/nfd/obj/bag")->move( this_object() );
			i--;
		}
	}
}
