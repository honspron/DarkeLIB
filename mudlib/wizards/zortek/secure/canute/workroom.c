//      from the Nightmare mudlib
//      an example workroom for new immortals

#include <std.h>

inherit ROOM;

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "Newbie wizard's workroom.");
    set("night long", "It is night outside.\nGo to bed.\n");
    set("day long", "It is day outside.\nGreetings and salutations.\n");
    set_exits( ({ "/d/standard/square", "/d/standard/adv_main" }),
      ({ "square", "hall" })
    );
    set_item_descriptions( ({ "item" }), ({ "This is an item in your room." }));
     set_smell("default", "It smells like Mikus has been changing some things.");
    set_listen("default", "You hear the sounds of code creation.");
}
