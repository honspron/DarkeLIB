#include <std.h>
inherit ROOM;

void create() {
    ::create();
    set_property("light", 5);
    set_property("indoors", 1);
    set("short", "In line.");
    set("long", "You are standing in line at the NTF soup kitchen waiting for a handout.\n");

        add_exit("/d/daybreak/room/ntf/ntfkitchen", "out");

	set_listen("default", "You hear the stomachs of the hungry, wretched and destitute thieves of the realms as they wait hungrily in line for a handout.\n");
	set_smell("default", "You smell the delicious aroma of a hot meal waiting for you at the end of the line!\n");
}
void reset() {
    ::reset();
if(!present("thief"))
{
new("/d/daybreak/mon/needythief.c")->move(this_object());
new("/d/daybreak/mon/needythief.c")->move(this_object());
new("/d/daybreak/mon/needythief.c")->move(this_object());
new("/d/daybreak/mon/needythief.c")->move(this_object());
}
}
