// /d/nfd/rooms/shops/tinker_storage
// EXCELSIOR!

inherit "/std/room";


void reset() {
	::reset();
	if(!present("music paper"))  
		new("/d/nfd/obj/ml_mpaper")->move(this_object());
	if(!present("card"))
		new("/d/nfd/obj/security_card")->move(this_object());
	if(!present("card 2"))
		new("/d/nfd/obj/security_card")->move(this_object());
	if(!present("card 3"))
		new("/d/nfd/obj/security_card")->move(this_object());
	if(!present("card 4"))
		new("/d/nfd/obj/security_card")->move(this_object());
}

void create() {
	::create();
	set_property("storage room",1);
	set("short","go away");
	set("long","blah");
	reset();
}
