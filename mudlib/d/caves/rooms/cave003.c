
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
    set_short("Narrow Corridor");
    set("long",@LONG
The corridor turns sharply here, growing wider at the north end.  To the southeast is the entrance to the complex.  Lichen and fungi on the ebon walls radiate an unearthly glow.  The floor seems to slope downwards.
LONG
    );
    set_smell("default", "It reeks of sweat here.");
    set_listen("default", "The only sound is the rapid beating of your heart.");
    set_items( ([
	({"lichen","fungi","fungus"}):
	"These small growths jut out from the smooth walls.",
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the north and southeast.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
      ]) );
    set_exits(([
	"southeast":ROOMS+"cave001",
	"north":ROOMS+"cave004",
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
	case 0..7:x=0;break;
	case 8..9:x=1;break;
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
	case 0..3:x=0;break;
	case 4..6:x=1;break;
	case 7..9:x=2;break;
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
	case 0..4:x=0;break;
	case 5..9:x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
