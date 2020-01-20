
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
    set_property("light", -3);
    set_property("indoors", 1);
    set_short("Small Temple");
    set("long",@LONG
You stumble into the entrance of a temple.  The walls are adorned with spiders of various sizes, as well as glyphs and sigils.  There are braziers emitting a foul smoke that reminds you of burning flesh.  Here and there is a mutilated corpse of someone foolish enough to come into the caves.  In the center of the room there is a massive statue.
LONG
    );
    set_smell("default", "The stench of blood is overpowering.");
    set_listen("default", "You hear screams of hopelessness and torment.");
    set_items( ([
	({"walls","wall"}):
	"The walls are covered with carved spiders.",
	({"spider","spiders","carved spider","carved spiders"}):
	"Carved from the obsidian walls, they are amazingly detailed.",
	({"glyph","glyphs","sigil","sigils"}):
	"Magical constructs, they pulse and glow with a deep crimson light.",
	({"brazier","braziers"}):
	"Brass burning containers, they are discolored from intense heat.",
	({"smoke","foul smoke"}):
	"It obscures your vision, burning your eyes.",
	({"corpse","corpses","body"}):
	"Dismembered and gutted, the corpses are horrible to look at.",
	({"statue","massive statue"}):
	"The statue is huge, easily ten feet tall.  It depicts an "+
	"incredibly beautiful female drow elf with supple breasts, flowing "+
	"white hair against ebon skin, and the lower body of a spider!  "+
	"Her face is contorted in a grimace of rage and hate.",
      ]) );
    set_exits(([
	"up":ROOMS+"cave008",
	"north":ROOMS+"cave010",
      ]));
}
void reset()
{
    int y,x;
    ::reset();
    if(!present("mage"))
    {
	switch(random(3))
	{
	case 0: x=1;break;
	case 1: x=2;break;
	case 2: x=3;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"mage")->move(TO);
	}
    }
    if(!present("warrior"))
    {
	switch(random(3))
	{
	case 0: x=1;break;
	case 1: x=2;break;
	case 2: x=3;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"warrior")->move(TO);
	}
    }
    if(!present("rogue"))
    {
	switch(random(3))
	{
	case 0: x=1;break;
	case 1: x=2;break;
	case 2: x=3;break;
	}
	for(y=0;y<x;y++)
	{
	    new(MON+"rogue")->move(TO);
	}
    }
}
