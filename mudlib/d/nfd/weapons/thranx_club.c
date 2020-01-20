// /d/nfd/weapons/thranx_club

// A nice heavy club



inherit "std/weapon";



void create() {

::create();

set_name("club");

set("id",({"A thranx's club","thranx club","club","a club"}));

set("short","thranx's club");

set("long","This is a large and heavy club that is perfect "+

"for thranx. You laugh- 'Hmm.  Is thranx plural thranx?' You "+

"should give up this adventuring life style and become a "+

"comedian! Woo woo!");

set_hit( (: call_other, this_object(), "weapon_hit" :) );

set_weight(120);

set_value( 250 );

set_ac(2);

set_wc(7,"crushing");

set_type("two handed blunt");

set_quality(3);

}



int weapon_hit() {

object where;

where = environment( this_object() );

if (living(where)) {

if((string)where->query_race() == "thranx") return 3;

}

}

