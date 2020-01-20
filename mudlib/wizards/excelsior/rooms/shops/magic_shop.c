// /wizards/excelsior/rooms/shops/magic_shop

#include <std.h>

inherit VAULT;

void reset() {
	::reset();
	if (!present("dippy")) new("/wizards/excelsior/rooms/shops/dippy")->move(
		this_object() );
}

void create() {
	::create();
	set_property("indoors",1);
	set_property("light",2);
	set("short","Dippy's Adventure Utilities");
	set("long","You are in the famous store, Dippy's Adventure Utilities. "+
		"Here can be found a plethora of magical and not so magical items "+
		"to aid any budding or experienced adventurer on their way. Dippy "+
		"is a die hard merchant, so unless he actually does die, his shop "+
		"will always be open. On the store counter is a list of Dippy's "+
		"products. There is a door leading east.");
	set_items( (["sign":"'say dippy, help' for assistance.",
		"door":"It leads to Dippy's storeroom." ]) );
	set_exits( (["southwest":"/wizards/excelsior/rooms/street2",
		"east":"/wizards/excelsior/rooms/shops/dippy_storage" ]) );
	set_door( "door","/wizards/excelsior/rooms/shops/dippy_storage",
		"east","geegee" );
	set_lock_level( "door", 25 );
	reset();
}
