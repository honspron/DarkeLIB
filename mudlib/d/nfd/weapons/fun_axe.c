// /d/nfd/weapons/fun_axe



inherit "std/weapon";



string *possible_messages;



void create() {

	::create();

	set("id",({"axe","fun axe","axe of fun"}) );

	set_name("axe");

	set("short","axe of fun.");

	set("long","Finally- an axe that is fun to use!");

        set_weight(100);

	set("value",120);

	set_ac( 3 );

	set_wc(5,"cutting");

	set_type("axe");

	set_quality(3);

	set_wield("Hahahaha! What fun this axe is!");

	set_hit( (: call_other, this_object(), "weapon_hit" :) );

	set_unwield("Fine. Don't have fun anymore.");

	set_value(120);

}



int weapon_hit(object attacker){

	string name;

	int ind,size;

	name = attacker->query_cap_name();

	possible_messages = ({"Hahaha! You dig the axe into "+name+"'s face!",

	"Woo! This axe is so much fun you wish you were it!","You swipe at "+

	name+" with your axe of fun laughing all the way.","Wheee! You get "+

	"carried away with your axe!","Mon-o-man is this axe fun!",

	"Hahahaha.","No wonder they call this the 'axe of fun'!","You wish "+

	"everyone could have this much fun while killing.","You attack "+

	name+" with a barrage of fun!"}) ;

	size = sizeof(possible_messages);

	ind = random(size);

	write( possible_messages[ind] );

	if ( ind == (size - 1) ) return 2;

	return 0;

}

