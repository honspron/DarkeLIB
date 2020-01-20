// /d/nfd/rooms/sewer2.6

#include <std.h>

inherit ROOM;

void reset() {
	::reset();
	if (present("manfrog")) { return; }
	else {
		new("/d/nfd/mon/manfrog")->move( this_object() );
		new("/d/nfd/mon/manfrog")->move( this_object() );
		new("/d/nfd/mon/manfrog")->move( this_object() );
	}
}

void create() {
	::create();
	set_property("light",-1);
	set_property("indoors",1);
	set("short","A mamoth intersection");
	set("long","You have come to a large intersection in the sewer system. "+
		"Tunnels head in almost every conceivable direction. However, there "+
		"is a trail of bread crumbs leading southeast. Hrm...");
	set_items( ([ ({"bread crumbs","crumbs"}):"They seem to beckon you to "+
			"go southeast."]) );
	set_exits( (["up":"/d/nfd/rooms/sewer2.6",
		"down":"/d/nfd/rooms/sewer2.6",
		"north":"/d/nfd/rooms/sewer2.6",
		"south":"/d/nfd/rooms/sewer2.6",
		"west":"/d/nfd/rooms/sewer2.6",
		"northeast":"/d/nfd/rooms/sewer2.6",
		"southwest":"/d/nfd/rooms/sewer2.6",
		"east":"/d/nfd/rooms/sewer2.7",
		"southeast":"/d/nfd/rooms/sewer3.7",
		"northwest":"/d/nfd/rooms/sewer_treasure" ]) );
	reset();
}
