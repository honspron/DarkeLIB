// /d/nfd/obj/bag

// my bag, gee



inherit "std/bag_logic.c";



void create() {

set_name("bag");

set("id",({"bag","a fine leather bag","leather bag"}));

set("short","A fine leather bag");

set("long","A fine leather bag that looks like it could carry "+

"stuff- but hey, that's what bags are for last anyone checked.");

set_weight( 40 );

set_value( 20 );

set_max_internal_encumbrance( 1000 );

}

