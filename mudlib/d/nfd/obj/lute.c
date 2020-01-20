// /d/nfd/obj/lute

// just what everyone always wanted! A LUTE!!!!!



inherit "/std/Object";



int charges;



void init() {

	::init();

	add_action("play","play");

}



void create() {

	::create();

	set_name("lute");

	set("id",({"bard lute","lute","bards lute","Bards lute","Bard's lute","bard's lute"}));

	set("short","The lute of a bard");

	set("long","If you want to, you may be able to "+

		"'play' this lute. Wonder what that does.");

	set_weight(200);

	set_value(30);

	charges = 3;

}



string query_short() { return ::query_short()+" ["+charges+"]"; }



string query_long() { 

	if(charges > 1) return ::query_long()+" What ever it does, it has "+

		charges+" strings remaining"; 

	if(charges == 1) return ::query_long()+" What ever it does, it only has "+

		charges+" string remaining"; 

	if(charges < 1) return ::query_long()+" What ever it does, it seems to have "+

		"NO strings remaining!"; 

}



int play(string str) {

	int i;

	object *inter;

	if(str != "lute") {

	  if(this_player()->query_level() > 8) {

                write("You are too high level and you break the lute.");

                this_object()->remove();

                return 1;

          }

              else



		notify_fail("What do you wish to play?\n");

		return 0;

	}

	write("You pluck a string on lute and it breaks. The world around you "+

		"begins to swirl and you find yourself elsewhere.");

	message("other_action",(string)this_player()->query_name()+" plucks "+

		"a string on a lute. The string breaks and "+(string)this_player()->

		query_subjective()+" fades into nothing.",environment(this_player()),

		({this_player()}));

	inter = users();

	i = sizeof(inter);

	i = random(i);

	while(wizardp(inter[i])) i++;

	this_player()->move_player(environment(inter[random(i)]));

	message("other_action","Playing a horrible melody on "+(string)this_player()->

		query_possessive()+" lute, "+(string)this_player()->query_name()+

		"spontaneously generates.",environment(this_player()),

		({this_player()}));

	if(!environment(this_player())) this_player()->move("/d/standard/square");

	charges--;

	return 1;

}

