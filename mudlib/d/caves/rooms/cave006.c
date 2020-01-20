
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
    set_short("Twisting Hall");
    set("long",@LONG
The air here grows heavy and cold, burning your lungs and pushing against you from all sides.  The passage continues to the west and back to the north.
LONG
    );
    set_smell("default", "You detect the scent of burnt flesh.");
    set_listen("default", "You hear a muffled scream...then...silence.");
    set_items( ([
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the north and west.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
      ]) );
    set_exits(([
	"north":ROOMS+"cave005",
	"west":ROOMS+"cave007",
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
	case 0..7: x=0;break;
	case 8..9: x=1;break;
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
	case 0..7: x=0;break;
	case 8..9: x=1;break;
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
	case 6..9: x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
