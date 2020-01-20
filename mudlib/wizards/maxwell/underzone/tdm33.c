//      From Maxwell's Underground mudlib
//        33rd Room of Dwarf Mining Zone

#include "/adm/include/std.h"
#include "under.h"
#define UNDER "/wizards/maxwell/underzone/"
//inherit "/wizards/maxwell/objects/etc/rope2";
inherit ROOM;

void init(){
    ::init();
}

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "You are crouched in a small crevice under the "
"breakdown.");
    set("long", 
"You are crouched in a small room at the end of the tunnel. The "
"center of the chamber has sunk down, breaking through the ceiling "
"of a room below, and creating a huge hole.\nYour feeble light in unable to penetrate very far "
"into the lower level. You think you can see some sort of stone floor "
"about forty feet below.\nA shiny new anchor bolt has been placed in "
"the wall here.\n"
        );
    set_exits( ({ "/wizards/maxwell/underzone/dm32",
 "/wizards/maxwell/underzone/dm41" }),
      ({ "east", "down" })
    );
    set_items( ([
       "hole" : "The hole leads straight down into the darkness below.",
       "anchor" : "The anchor consists of a steel rod with a loop at one "
                   "end. The rod has been hammered into the wall.",     
       "bolt"   : "The anchor consists of a steel rod with a loop at one "
                   "end. The rod has been hammered into the wall.",     
      ]) );
       set_smell("default", "The dust floating through the air is making "
"it hard to breathe.");
//Rope Code
//      rope_target = ({"hole"});
//      target_tie  = ({ "anchor","bolt" });
//      rope_dest   = ({ (UNDER+"dm41"),(UNDER+"dm33")"down"});
}

