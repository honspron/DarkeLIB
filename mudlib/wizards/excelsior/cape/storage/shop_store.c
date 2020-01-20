// /wizards/excelsior/cape/storage/shop_store
// Excelsior 
// 9-29-96

inherit "/std/vault";

void reset() {
	::reset();
	
	
	
}

void create() {
	::create();
	set("short","The general store storage room");
	set("long","This is where stuff is stored. Go away.");
	add_exit("/wizards/excelsior/cape/rooms/general_store","south");
	set_door("door","/wizards/excelsior/cape/rooms/general_store","south",
		"cape shop 1 key");
	set_property("storage room",1);
	reset();
}

