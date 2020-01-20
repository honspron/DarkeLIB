// /wizards/excelsior/rooms/shops/office_storage
// Excelsior 7/3/96

inherit "/std/room";
void reset() {
	::reset();
	if(!present("clue")) 
		new("/wizards/excelsior/obj/clue")->move(this_object());
	if(!present("map")) 
		new("/wizards/excelsior/obj/world_map")->move(this_object());
	if(!present("map 2")) 
		new("/wizards/excelsior/obj/world_map")->move(this_object());
	if(!present("mystic compass")) 
		new("/wizards/excelsior/obj/mystic_compass")->move(this_object());
	if(!present("rations pack"))
		new("/wizards/diewarzau/obj/misc/rations_pack")->move(this_object());
	if(!present("rations pack 2"))
		new("/wizards/diewarzau/obj/misc/rations_pack")->move(this_object());
	if(!present("rations pack 3"))
		new("/wizards/diewarzau/obj/misc/rations_pack")->move(this_object());
	if(!present("rations pack 4"))
		new("/wizards/diewarzau/obj/misc/rations_pack")->move(this_object());
	if(!present("rations pack 5"))
		new("/wizards/diewarzau/obj/misc/rations_pack")->move(this_object());
	if(!present("physical compass")) 
		new("/wizards/excelsior/obj/physical_compass")->move(this_object());
	if(!present("physical compass 2")) 
		new("/wizards/excelsior/obj/physical_compass")->move(this_object());
	if(!present("chest"))
		new("/wizards/diewarzau/obj/misc/small_chest")->move(this_object());
}

void create() {
	::create();
	set("short","leave");
	set_property("storage room",1);
	reset();
}
