// /wizards/excelsior/rooms/shop/dippy_storage

#include <std.h>
#define ITEMS_TO_SELL ({"/wizards/excelsior/obj/lesser_explosive","/wizards/excelsior/obj/light_crystal","/wizards/excelsior/obj/dark_crystal","/wizards/excelsior/obj/ticket"})
#define NUMBER_PER_ITEM 5

inherit VAULT;

void create() {
	::create();
	set_property("storage room",1);
	set_property("light",1);
	set_property("indoors",1);
	set("short","In the store room");
	set("long","Despite the numerous signs posted about reading 'TRESPASSERS "+
		"WILL BE BEHEADED' you seem to have found your way into Dippy's storage "+
		"room. This is where all of Dippy's items are stored while waiting to "+
		"be sold.");
	set_items( (["sing":"You take no notice of their message"
		]) );
	set_exits( (["west":"/wizards/excelsior/rooms/shops/magic_shop"
		]) );
	set_door("door","/wizards/excelsior/rooms/shops/magic_shop","west","geegee");
	reset();
}

void reset() {
	object *what;
	int i,n;
	::reset();
	set_open("door",0);
	set_locked("door",1);
	"/wizards/excelsior/rooms/shops/magic_shop"->set_open("door",0);
	"/wizards/excelsior/rooms/shops/magic_shop"->set_locked("door",1);
	what = all_inventory( this_object() );
	i = sizeof( what );
	while ( i-- ) {
		what[i]->remove();
	}
	n = NUMBER_PER_ITEM;
	i = sizeof( ITEMS_TO_SELL );
	while ( i-- ) {
		while( n > -1 ) {
			new( ITEMS_TO_SELL[i] )->move( this_object() );
			n--;
		}
		n = NUMBER_PER_ITEM;
	}
}
