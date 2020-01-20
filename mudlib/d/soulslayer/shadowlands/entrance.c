#include <std.h>

inherit ROOM;

void create() {
    ::create();
    
    // 5 to -5
    set_property("light", 1);
    set_property("indoors", 1);

    set("short", "Short title/description");
    set("night long", "Night description.\n");
    set("day long", "Day description.\n");

    set_exits( ([
    	"out"     : "/wizards/soulslayer/workroom"
    ]));

    set_listen("default", "Listen description.\n");
}

void reset() {
    ::reset();
}
