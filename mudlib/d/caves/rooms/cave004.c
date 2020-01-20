
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
You seem to have reached a dead end.  The cold stone of the tunnel seems to weigh heavily upon you now.  It feels colder here, a slight breeze pushing cold air from the west.  The shadows writhe violently.
LONG
    );
    set_smell("default", "Acrid smoke assaults your nostrils.");
    set_listen("default", "Twisted chanting breaks the silence.");
    set_search("default","Your hand passes through the west wall, "+
      "exposing it as some trick of sorcery!");
    set_items( ([
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the west and south.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.  "+
	"The west wall seems strange, and could use further scrutiny.",
	({"west wall"}):
	"As you concentrate on the wall, it vanishes, only to reappear again.",
      ]) );
    set_exits(([
	"west":ROOMS+"cave005",
	"south":ROOMS+"cave003",
      ]));
    add_invis_exit("west");
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
	case 0..3: x=0;break;
	case 4..5: x=1;break;
	case 6..7: x=2;break;
	case 8..9:x=3;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
