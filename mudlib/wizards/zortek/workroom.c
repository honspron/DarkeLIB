#include <std.h>

inherit ROOM;

void create() {
    ::create();
    set_no_clean(1);
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "Zortek's Morgue");
    set("night long", @NIGHT
You feel the uncomfortable presence of night.  It is not in the degree
of light or any indication from an outside source; however, you know in
your heart the Legions of the Darke are on the prowl.
NIGHT
);
    set("day long", @DAY
The morgue here seems to be lacking in life and luster.  This could be due
to the overwhelming feeling that the forces of Darkeness are held at bay
by the power of solar luminance.  There is nothing in this spherical room
except for a scribble mark in the northern corner.
DAY
);
    add_exit("/d/damned/guilds/join_rooms/cleric_join", "cleric");
    add_exit("/wizards/zortek/canyon/room/entry", "canyon");
    add_exit("/d/damned/akkad/ak_center", "center");
}
