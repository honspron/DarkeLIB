// /wizards/excelsior/weapons/paring_knife
// a sorry knife
inherit "std/weapon";

void create() {
::create();
set_name("knife");
set("id",({"paring knife","knife","a paring knife"}) );
set("short","paring knife");
set("long","Not much of a weapon, but you guess the thranx "+
"that it was owned by was desperate for a weapon. You should "+
"probably just sell it, unless you are desperate, too.");
set_ac( 0 );
set_wc( 1, "cutting" );
set_type("knife");
set_quality( 0 );
set_weight( 200 );
set_value( 3 );
}
