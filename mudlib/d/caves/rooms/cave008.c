
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
    set_property("light", -2);
    set_property("indoors", 1);
    set_short("Sinkhole");
    set("long",@LONG
There is very little light here.  In the center of the room is a fissure leading down to the depths below.  Water slowly trickles from apparently everywhere, running down into the fissure.
LONG
    );
    set_smell("default", "It reeks of moisture and decay.");
    set_listen("default", "Water drips incessantly.");
    set_items( ([
	({"fissure","hole"}):
	"An opening that leads down into inky blackness.",
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the south and down.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
      ]) );
    set_exits(([
	"south":ROOMS+"cave007",
	"fissure":ROOMS+"cave009",
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
	case 0..8: x=0;break;
	case 9: x=1;break;
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
	case 0..5: x=2;break;
	case 6..8: x=3;break;
	case 9: x=4;break;
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
	case 0..5: x=3;break;
	case 6..7: x=0;break;
	case 8..9: x=4;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
