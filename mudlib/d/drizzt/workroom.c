//      from the Nightmare mudlib
//      an example workroom for new immortals

#include <std.h>


inherit "/std/locker_room";
void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set_no_clean(1);
    set("short", "Newbie wizard's workroom.");
    set("night long", "It is night outside.\nGo to bed.\n");
    set("day long", "It is day outside.\nGreetings and salutations.\n");
    set_exits( ({ "/d/standard/square", "/d/standard/adv_main" }),
      ({ "square", "hall" })
    );
    add_exit("/d/damned/akkad/ak_center", "tran");
    add_exit("/d/damned/virtual/bregan-daerthe_hall_6.clan_strong", "sb");
    add_exit("/wizards/misery/arena/booths_room","arena!");

     set_smell("default", "It smells like Mikus has been changing some things.");
    set_listen("default", "You hear the sounds of code creation.");
}
