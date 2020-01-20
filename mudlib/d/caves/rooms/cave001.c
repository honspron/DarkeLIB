
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
    add_action("do_clear","clear");
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
    set_property("light",0);
    set_property("night light",-1);
    set_property("indoors", 0);
    set_short("Cave of Darkness");
    set("day long",@DAY
This is a small cave set into the side of a hill.  For years it has been whispered that the entrance to a drow city was located near here.  Of course that has never been proven, anyone who explores the depths vanishes.  Sunlight shines down in thin wispy strands, not really illuminating much as the black walls, floor, and ceiling seem to gobble nearly all light.  A %^BOLD%^%^YELLOW%^HUGE%^RESET%^ sign catches your eye, better read it.
DAY
    );
    set("night long",@NIGHT
This is a small cave set into the side of a hill.  It seems much more sinister under the cover of night.  Shadows dance and loom, twisting this way and that.  The cold black stone walls, ceiling, and floor appear to draw warmth from your body.  A %^BOLD%^%^YELLOW%^HUGE%^RESET%^ sign catches your eye, better read it.
NIGHT
    );
    set_smell("default", "You smell fear.");
    set_listen("default", "You hear muffled footsteps.");
    set_items( ([
	({"light","strand","strands","sunlight"}):
	"The light appears to wither, as if something were consuming it.",
	({"shadow","shadows"}):
	"The shadows shift and move, deepening to the northeast and northwest.",
	({"wall","walls","floor","ceiling"}):
	"The walls, floor, and ceiling are made of smooth, cold, black obsidian.",
	({"sign","huge sign"}):
	"Don't just look at it, read it!",
      ]) );
    set_exits(([
	"northeast":ROOMS+"cave002",
	"northwest":ROOMS+"cave003",
	"out":"/d/damned/virtual/room_8_22.world",
      ]));
    set_pre_exit_functions( ({"northwest"}), ({"go_northwest"}) );
    set_pre_exit_functions( ({"northeast"}), ({"go_northeast"}) );
}
int go_northwest()
{
    if(!TP->query_property("warned")||!TP->is_player())
    {
	write("%^BOLD%^%^BLUE%^Cyric bellows: %^BOLD%^%^YELLOW%^You will "+
	  "go no further without heeding the warning!%^BOLD%^%^GREEN%^\n\n"+
	  "The sign glows briefly.%^RESET%^");
	write_file(LOGS+"/repel.log", TPQCN+
	  " was repelled at "+ctime(time())+
	  ".\n");
	return 0;
    }
    else return 1;
}
int go_northeast()
{
    if(!TP->query_property("warned"))
    {
	write("%^BOLD%^%^BLUE%^Cyric bellows: %^BOLD%^%^YELLOW%^You will "+
	  "go no further without heeding the warning!%^BOLD%^%^GREEN%^\n\n"+
	  "The sign glows briefly.%^RESET%^");
	write_file(LOGS+"/repel.log", TPQCN+
	  " was repelled at "+ctime(time())+
	  ".\n");
	return 0;
    }
    else return 1;
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
	case 0..7:x=0;break;
	case 8..9:x=1;break;
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
	case 0..7:x=0;break;
	case 8..9:x=1;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
int do_clear(string str)
{
    if(!str)
    {
	notify_fail("Clear what?\n");
	return 0;
    }
    if(str != "me")
    {
	notify_fail("clear me\n");
	return 0;
    }
    write("BAM!  Cleared.");
    TP->remove_property("warned");
    return 1;
}
int read_sign(string str)
{
    if(!str)
    {
	notify_fail("Read what?\n");
	return 0;
    }
    else if(str=="sign")
    {
	write("\n%^BOLD%^%^YELLOW%^Beware, foolish mortals, your precious life "+
	  "is about to come to a swift, brutal end.\n\n"+
	  "%^BOLD%^%^BLUE%^Cyric, the Prince of Lies     ///C///%^RESET%^");
	TP->set_property("warned",1);
	write_file(LOGS+"/warning.log", TPQCN+
	  " read the warning at "+ctime(time())+
	  ".\n");
	return 1;
    }
}
