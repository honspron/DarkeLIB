// /d/nfd/obj/lesser_explosive

// blowin things up! woo!



#include <std.h>



inherit OBJECT;



int time;



void init() {

	::init();

	add_action("blow","light");

}



void create() {

	::create();

	set_name("explosive");

	set("id",({"explosive","blow up thing"}) );

	set("short","An explosive");

	set("long","This is an explosive built to hurt anyone in the room with it. "+

		"To use it simply 'light' the 'fuse'. It will damage everything in "+

		"the room you put it in.");

	set_weight( 300 );

	set_value(470 );



}



void blow_up() {

	object env,*inv;

	int i;

	env = environment( this_object() );

	if ( living(env) ) {

		env->add_hp( -52 );

		tell_object( env,"Wtf! Your explosive explodes in your hand! Ouch!");

		tell_room( environment( env ), "A bomb explodes in "+env->query_cap_name()+

			"'s hands. Ouch!", ({env}) );

		remove();

		return;

	}

	inv = all_inventory( env );

	i = sizeof( inv );

	i--;

	while ( i > -1 ) {

		if ( inv[i]->living() ) {

			inv[i]->add_hp( -29 );

		}

		i--;

	}

	tell_room( env,"A bomb explodes in the area hurting everyone here!");

	remove();

}



void warning() {

	object env;

	if (time < 1) {

		blow_up();

		return;

	}

	env = environment( this_object() );

	if ( env->is_player() ) {

		tell_object( env, "The fuse on the explosive burns." );

		time--;

		call_out( "warning", 3 );

		return;

	}

	else

	{

		tell_room( env, "The fuse on the explosive burns." );

		time--;

		call_out( "warning", 3 );

		return;

	}

}



int blow( string str ) {

	if (str == "fuse") {

		if (time) {

			write("The fuse has already been lit.");

			return 1;

		}

		write("You light the fuse on your explosive.");

		time = 4;

		call_out( "warning", 3, );

		return 1;

	}

	notify_fail("Light what?\n");

	return 0;

}

