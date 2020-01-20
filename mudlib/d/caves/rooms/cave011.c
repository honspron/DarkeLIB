
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
    set_property("light", -4);
    set_property("indoors", 1);
    set_short("Altar of the Spider Queen");
    set("long",@LONG
The tunnel ends here.  You are surrounded by cold stone walls.  This room is devoid of items except the altar.  It stands 3 feet tall and is at least seven feet from one end to the other.  A sinister aura eminates from the cold stone altar.  The only direction you can go is to the south.
LONG
    );
    set_smell("default", "The air has a musty smell.");
    set_listen("default", "There is deathly silence.");
    set_items( ([
	({"tunnel"}):
	"The tunnel you have been traveling is cut flawlessly from obsidian.",
	({"wall","walls","ceiling","floor"}):
	"There are no visible cracks or crevices in the polished stone.",
	({"altar","dark altar","spider altar"}):
	"Three feet tall and seven foot by seven foot wide, the altar is "+
	"huge.  At first glance, the surface seems to be flat, but upon "+
	"further scrutiny, you realize some abnormalities.  There are "+
	"deep grooves that run like veins towards the front of this "+
	"foul construct.  The surface slopes inwards slightly, "+
	"to a depression in the center.  You notice a small hole "+
	"whose function is not immediately apparent.  Glancing down, "+
	"you see a small bronze bowl of blood at the front of the altar.",
	({"groove","grooves","vein","veins"}):
	"These grooves channel blood to the bowl at the altar's base.",
	({"depression","hole"}):
	"The blood collects from the grooves, down the hole, into the bowl.",
	({"bowl","small bowl","bronze bowl","small bronze bowl"}):
	"Obviously used for sacrifices, this bronze bowl seems to be "+
	"fused to the stone it rests upon.",
      ]) );
    set_exits(([
	"south":ROOMS+"cave009",
      ]));
}
void reset()
{
    ::reset();
    if(!present("mage"))
    {
	switch(random(5))
	{
	case 0: new(MON+"mage")->move(TO);
	    break;
	case 1: new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    break;
	case 2: new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    break;
	case 3: new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    break;
	case 4: new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    new(MON+"mage")->move(TO);
	    break;
	}
    }
}
