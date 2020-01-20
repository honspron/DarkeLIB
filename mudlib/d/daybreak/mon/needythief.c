// /d/nfd/mon/thief

#include <std.h>
#include <daemons.h>
#include <clock.h>

inherit MONSTER;


void create() {
	::create();
	set_name("beggar");
	set("id",({"thief","criminal","crook","robber","beggar"}) );
	set_level( 10 );
	set_fingers( 5 );
      set("short", "A crooked little beggar");
	set("long","This dirty little beggar is standing around smelling up the place.");
	set("race", "high elf");
	set("gender", "male");
	set_body_type("human");
	set_overall_ac( 6 );
	set_skill("melee",60);
	set_skill("knife",60);
	set_skill("perception",60);
	set_skill("pick pocket",95);
	set_skill("stealth",40);
	set_skill("dodge",30);
	set_skill("parry",35);
	set_skill("reverse stroke",55);
	set_stats("dexterity",95);
	set_skill("attack",70);
	set_skill("thrown",30);
	set_class("thief");
        set_money("silver", 50);
	set("aggressive",(: call_other, this_object(),"check_attack" :) );
	call_out("reset",1);
}

int check_attack(object ob) {
	int ran;
      if((string)ob->query_name() == "beggar") return 0;
	if((string)EVENTS_D->query_time_of_day() == "day") {
		ran = 7;
	}
	if((string)EVENTS_D->query_time_of_day() == "night") {
		ran = 4;
	}
	if (!ran) {
		ran = random(2)+5;
	}
	if (!random(ran)) return 1;
	return 0;
}

int check_if_living(object ob) {
	if(ob == this_object()) return 0;
if(living(ob) && (string)ob->query_name() != "beggar") return 1;
	return 0;
}

void heart_beat() {
	object who,*stuff,*stuff2;
	int check,i,my_silver,your_silver;
	::heart_beat();
	if(present("coins",environment(this_object()))) 
		force_me("get coins");
	if ((string)EVENTS_D->query_time_of_day() == "day") {
		i = 3;
	} else {
		i = 2;
	}
	if (random(i) == 0) return;
	stuff2 = all_inventory( environment( this_object()));
	stuff = filter_array( stuff2, "check_if_living", this_object() );
	i = sizeof(stuff);
	if (!stuff || !i) return;
	i--;
	while ( i > -1 ) {
		if((string)stuff[i]->query_name() != "thief") {
		if(random(6) == 0)	{
			if(check > 2) return;
			force_me("use pick pocket at "+stuff[i]->query_name());
			check++;
		}}
		i--;
	}
	if (!present("knife",this_object())) return;
	if (random(31) == 0) {
		my_silver = query_money("silver");
		who = stuff[random(sizeof(stuff))];
		your_silver = who->query_money("silver");
		if(!your_silver) return;
		tell_object( who, "%^YELLOW%^%^BOLD%^The thief steals some of your "+
			"silver at knife point!" );
		tell_room(environment(this_object()),"The thief steals some of "+
			who->query_cap_name()+"'s silver at knife point!", ({who,this_object()}));
		i = random(your_silver);
		who->add_money("silver",-i);
		set_money("silver",my_silver+i);
	}
}
