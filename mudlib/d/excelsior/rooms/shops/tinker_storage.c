// /wizards/excelsior/rooms/shops/tinker_storage
// EXCELSIOR!

inherit "/std/room";


void reset() {
	::reset();
	if(!present("music paper"))  
		new("/wizards/excelsior/obj/ml_mpaper")->move(this_object());
	if(!present("card"))
		new("/wizards/excelsior/obj/security_card")->move(this_object());
	if(!present("card 2"))
		new("/wizards/excelsior/obj/security_card")->move(this_object());
	if(!present("card 3"))
		new("/wizards/excelsior/obj/security_card")->move(this_object());
	if(!present("card 4"))
		new("/wizards/excelsior/obj/security_card")->move(this_object());
}

void create() {
	::create();
	set_property("storage room",1);
	set("short","go away");
	set("long","blah");
	reset();
}
