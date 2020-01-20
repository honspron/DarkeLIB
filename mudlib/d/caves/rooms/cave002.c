
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
    set_short("Dead End");
    set("long",@LONG
The passage ends abruptly.  There is simply no where to go but the way you came from.  There is a small puddle in the corner.  An object hangs from the ceiling.
LONG
    );
    set_smell("default", "The air has a coppery scent.");
    set_listen("default", "You hear a slow drip drip drip.");
    set_items( ([
	({"object","hanging object"}):
	"It appears to be a body.",
	({"corpse","carcass","body"}):
	"This is a body of a wood elf, disemboweled, its entrails dangling.",
	({"puddle","pool"}):
	"Looking closer, you realize it is a small puddle of blood.",
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the southwest.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
      ]) );
    set_exits(([
	"southwest":ROOMS+"cave001",
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
	case 0..3: x=0;break;
	case 4..6: x=1;break;
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
	case 0..4: x=0;break;
	case 5..9: x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
