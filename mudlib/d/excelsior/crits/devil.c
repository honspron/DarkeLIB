// /wizards/excelsior/crits/devil
// must be in above location for Aether crits to function
// Excelsior, 4-11-96

inherit "std/monster";

void create() {
	::create();
	set_name("devil");
	set("id",({"devil","satan","beelzybub","the devil","evil incarnate"}));
	set_level(30);
	set("short","The devil himself");
	set("long","This is satan himself, evil to all end. Maybe you could ask "+
		"him for 'help'.");
	set("race","god");
	set("gender","neuter");
	set_body_type("human");
	set_overall_ac(50);
	set_languages( ({"common","yin","serra","dwarvish","middle-english","treefolk"
		"Vr'krr","undead-tongue","elvish"}) );
}

void directed_message(object from,string what) {
	force_me("speak "+(string)from->query_primary_lang());
	if(!query_primary_lang()) force_me("speak common");
	if(what == "help") {
		force_me("say Hrm. You want to go back to life do you? Well, "+
			"I'm a fair incarnation of all evil. If you can tell me "+
			"the answer to this question, I will let you return to "+
			"the living. What is the noblest quest of them all? HA! "+
			"*snicker* anybody who finds themselves here will never get "+
			"this one!");
		message("info","You can tell the answer to the devil with "+
			"'say devil, answer <answer>'.",from);
		return;
	}
	if(what[0..2] != "ans") return;
	sscanf(what,"answer %s",what);
	if(what == "love") {
		force_me("say %^RED%^WHAT?!?!?! %^BOLD%^NOBODY EVER ANSWERS THAT QUESTION "+
			"RIGHT! %^RESET%^%^BLUE%^%^BOLD%^BE GONE!!!!!!");
		message("info","You feel your body fading and suddenly appear somewhere "+
			"else.",from);
		from->move("/d/damned/akkad/ak_center");
		message("info","A door on the side of the statue opens up, and out "+
			"comes "+(string)from->query_cap_name()+".",environment(from),({from}));
		return;
	}
	force_me("say Sorry, that is not the correct answer.");
}
		
