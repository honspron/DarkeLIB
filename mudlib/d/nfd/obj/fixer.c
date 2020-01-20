// /d/nfd/obj/fixer

// will restore someone's health with no penalties except to your own mp



#include <std.h>



inherit OBJECT;



void init() {

	::init();

	add_action("fix_him","heal"); /* I am a sexist pig. Notice my use of 'him', */

}								  /* instead of a politically correct

									 function name like 'person' */

void create() {

	::create();

	set_name("fixer");

	set("id",({"fixer","healer"}) );

	set("short","The Moo cow's personal healer");

	set("long","This is a strange magical device made out of a fishing pole "+

		"that someone managed to flush down the toilet. It was built by the "+

		"New Faerie Dust sewer cows. You somehow feel that if you 'heal <living>' "+

		"that creature's (a player or npc's) health will be restored entirely for "+

		"only the cost of "+

		"a few mp's. Wow, neat!");

	set_weight( 198 );

	set_value( 795 );

}



int fix_him( string str ) {

	object who;

	int max_hp,max_mp,max_mp_tp,healed_hp,healed_mp,total_healed,hp,mp,diff;

	if (!str) {

		notify_fail("Heal who?\n");

		return 0;

	}

	if ( living( environment( this_object() ) ) ) {

		who = present( str, environment( environment( this_object())));

	} else {

		who = present( str );

	}

	if (!who) {

		notify_fail("The person you wish to heal must be in the same room as "+

			"you.\n");

		return 0;

	}

	max_mp_tp = this_player()->query_max_mp();

	max_hp = who->query_max_hp();

	max_mp = who->query_max_mp();

	hp = who->query_hp();

	mp = who->query_mp();

	healed_hp = max_hp-hp;

	healed_mp = max_mp-mp;

	who->set_hp( max_hp );

	who->set_mp( max_mp );

	total_healed = healed_mp + healed_mp;

	total_healed = total_healed/2;

	diff = max_mp_tp-total_healed;

	if ( diff < 10 ) { this_player()->set_mp( 25 ); }

	else { this_player()->add_mp( -total_healed ); }

	write("The healer dissolves after healing your target.");

	this_object()->remove();

	return 1;

}

	

