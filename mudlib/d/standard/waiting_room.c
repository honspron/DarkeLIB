inherit "/std/room";



void create() {

    ::create();

    set_property("light", 2);

    set_property("indoors", 1);

    set_property("no attack", 1); 

    set_property("no scry", 1);

    set_property("no teleport", 1);

    set_property("no summon", 1);

    set_property("no cast", 1);

    set("long", "This is the waiting room, you are in the creation process.");

}



