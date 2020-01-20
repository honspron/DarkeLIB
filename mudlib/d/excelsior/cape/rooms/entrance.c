// /wizards/excelsior/cape/rooms/entrance
// here we go again

inherit "/std/room";

void create() {
	::create();
	set_property("indoors",0);
	set_property("light",3);
	set("short","On a small path to South Cape");
	set("long","You are walking along a cute little path to the small coastal "+
		"village of South Cape. The path is lined with beautiful flowers. "+
		"This town is obviously well maintained. Everything is clean and "+
		"well kept, and you are still in the wilderness surrounding the "+
		"town itself. The path to town continues south, while to the "+
		"north you can step back into the more hostile swamp.");
	set_items((["flowers":(: this_object(),   "flower" :),
		"path":"It is a well maintained dirt path. The shrubery along "+
			"its edge is well trimmed. Despite the paths apparent "+
			"flawlessness, something about it bothers you. Perhaps "+
			"a search is in order!",
		({"village","town","south cape"}):"It is not quite in view yet.",
		"swamp":"Why go to the swamp when you could go to the village? Bog."]));
	set_exits((["north":"/d/damned/virtual/"
,
		"south":"/wizards/excelsior/cape/rooms/rm2"]));
	set_search("path",(: this_object(),   "path" :));
	set_listen("default","You hear bees buzzing in the air.");
	set_smell("default","You smell the scent of flowers.");
}

void flower() {
	int i;
	string *exits;
	write("You bend over to smell the pretty flowers and get stung by a bee! You "+
		"yell out in pain! Yeeeooooowwwwww!!!!");
	exits = query_exits();
	i = sizeof(exits);
	message("other_action",(string)this_player()->query_cap_name()+" bends over "+
		"to smell some flowers and quickly leaps up in pain.",
		this_object(),({this_player()}));
	message("other_action","%^RED%^%^BOLD%^"+(string)this_player()->query_cap_name()+
		"yells:%^RESET%^ Yeeeooooowwwwww!!!!",this_object(),({this_player()}));
	while(i--)
		message("other_action","%^RED%^%^BOLD%^You hear "+
			(string)this_player()->query_cap_name()+" yell in the distance:%^RESET%^"+
			" Yeeeooooowwwwww!!!!",query_exit(exits[i]));
}

void path() {
	write("You search the path and find a strange string half buried in the "+
		"dirt. You pull on the string and fall into darkness as the path opens "+
		"up beneath your feet.");
	message("other_action",(string)this_player()->query_cap_name()+" pulls on a "+
		"small string "+(string)this_player()->query_subjective()+" found on "+
		"the ground. The path beneath him opens up and he falls into darkness. "+
		"The path closes again.",this_object(),({this_player()}));
	this_player()->move_player("/wizards/excelsior/cape/rooms/under1");
}
