// /d/nfd/obj/juggling_club

// Excelsior 7-1-96



inherit "/std/weapon";



void create() {

	::create();

	set_name("club");

	set("id",({"club","juggling club"}));

	set("short","juggling club");

	set("long","This is a juggling club typically used for juggling. You too "+

		"can 'juggle' it. You can also use it as a weapon.");

	set_weight(70);

	set_float_value(0.6);

	set_ac(1);

	set_wc(2,"crushing");

	set_type("blunt");

	set_quality(6);

	set_verb("pound");

	set_material("/misc/wood");

}



void init() {

	::init();

	add_action("juggle","juggle");

}



int juggle(string str) {

	if(str != "club") {

		notify_fail("Juggle what?\n");

		return 0	; }

	write("You juggle the club and bonk yourself on the head. You're getting better!");

	message("other_action",(string)this_player()->query_cap_name()+" juggles "+

		"a juggling club and hits "+(string)this_player()->query_accusative()+

		"self on the head. Jesus.");

	this_player()->add_hp(-1);

	return 1;

}



int is_right_club() { return 1; }

