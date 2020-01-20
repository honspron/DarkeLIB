
#include <std.h>
#include "cyric.h"
inherit "std/room";

void init()
{
    ::init();
    if(TP->query_ghost())
    {
	call_out("do_church",0);
	return;
    }
    if(TP->shadow_form())
    {
	call_out("do_church",0);
	return;
    }
    add_action("read_sign", "read");
}
void do_church(object tp)
{
    write(@WARN
%^BOLD%^%^BLUE%^Cyric bellows: %^BOLD%^%^YELLOW%^BEGONE!%^RESET%^
WARN
    );
    write_file(LOGS+"/church.log", TPQCN+
      " was sent to church at "+ctime(time())+
      ".\n");
    TP->move_player("/d/standard/square");
    return;
}
void create()
{
    ::create();
    set_property("light", -1);
    set_property("indoors", 1);
    set_short("Carved Tunnel");
    set("long",@LONG
The tunnel twists again, sharply.  The passage you are in branches to the north and east.  The walls are smooth, too smooth to be created by human hands.  It is if a mighty river once forced its way through here, creating a channel with no visible fissures.  A feeling of malevolent magic permeates the area.
LONG
    );
    set_smell("default", "The air has the taint of ozone.");
    set_listen("default", "A loud crackling reaches your ears.");
    set_items( ([
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the east and north.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
      ]) );
    set_exits(([
	"east":ROOMS+"cave006",
	"north":ROOMS+"cave008",
      ]));
}
void reset()
{
    int y,x;
    ::reset();
    if(!present("mage"))
    {
	switch(random(10))
	{
	case 0..4: x=0;break;
	case 5..9: x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"mage")->move(TO);
	}
    }
    if(!present("warrior"))
    {
	switch(random(10))
	{
	case 0..6: x=0;break;
	case 7..9: x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"warrior")->move(TO);
	}
    }
    if(!present("rogue"))
    {
	switch(random(10))
	{
	case 0..8: x=0;break;
	case 9: x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
