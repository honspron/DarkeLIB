
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
    set_short("Twisted Corridor");
    set("long",@LONG
The passage twists sharply again, leading south into the shadows and east back towards the exit.  You begin to realize you could easily get lost if you didn't keep your bearings.
LONG
    );
    set_smell("default", "Acrid smoke assaults your nostrils.");
    set_listen("default", "Twisted chanting breaks the silence.");
    set_items(([
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the east and south.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
      ]));
    set_exits(([
	"east":ROOMS+"cave004",
	"south":ROOMS+"cave006",
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
	case 0..6: x=0;break;
	case 7..9: x=1;break;
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
	case 0..1: x=0;break;
	case 2..3: x=1;break;
	case 4..5: x=2;break;
	case 6..7: x=3;break;
	case 8..9: x=4;break;
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
	case 0..5: x=0;break;
	case 6..7: x=1;break;
	case 8..9: x=2;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
