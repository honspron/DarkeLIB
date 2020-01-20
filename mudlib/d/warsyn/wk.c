#include <std.h>
inherit ROOM;

void create() {

    ::create();
    seteuid(getuid());
    set_property("light",3);
    set_property("indoors",1);
    set("short", "Endless void of wasted life and space");
    set("long", "This place is a void of wasted time and space. " +
         "It is lonely and makes you feel tired.");
    add_exit("/wizards/warsyn/monastery/walk1","path");
    add_exit("/d/standard/square","square");
    add_exit("/d/standard/adv_main","hall");
    add_exit("/d/standard/adv_inner","boards");
}
