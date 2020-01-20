// /d/nfd/rooms/shops/office_clerk
// Excelsior is burning up his keyboard creating objects so fast
// 7/2/96
// Do not remove this header (bog)

inherit "/std/npc_shop";

int gave;

void reset() {
	::reset();
	gave = 0;
}

void create() {
	::create();
	set_name("clerk");
	set("id",({"office clerk","shopkeeper","happy clerk","happy office clerk"}));
	set("short","A happy office clerk");
	set("long","This happy office clerk is young a jovial. "+
		"He looks hecka ready to help you. He wears a button "+
		"that reads: 'say shopkeeper, help' for assistance. You "+
		"may be able to tell him to 'talk' as well.");
	set_level(7);
	set("race","human");
	set_gender("male");
	set_body_type("human");
	set_overall_ac(7);
	set_money("silver",500);
	set_melee_damage("strikes");
	set_property("magic resistance",75);
	set_skill("melee",56);
	set_skill("martial arts",50);
	set_class("fighter");
	set_languages(({"middle-english","common","serra","elvish","dwarvish",
		"treefolk"}));
	set("storage room","/d/nfd/rooms/shops/office_storage");
	set("markup",-15);
	set("no sell",1);
	reset();
}

void directed_message(object from, string str) {
	set_primary_lang((string)from->query_primary_lang());
	if(!query_primary_lang()) set_primary_lang("common");
	if(str != "talk")  { ::directed_message(from,str);
return; }
	force_me("say Why, I didn't always like working here. In fact I "+
		"started to pay off the money lost when I broke my grandma's "+
		"lute. Do you have a lute? Well anyway now I have realized that "+
		"the job security offered here is more than worth the low wages.");
}

void catch_tell(string str) {
	string who;
	object person;
	if(sscanf(str,"%s gives you The lute of a bard",who) == 1) {
		person = present(who);
		if(!person) return;
		if(!present("lute",this_object())) return;
		set_primary_lang((string)person->query_primary_lang());
		if(!query_primary_lang()) set_primary_lang("common");
		if(!present("lute")->is_right_lute()) {
			command("say this lute isn't very good.");
			return;
		}
		command("say wow! It's just like I always dreamed! Now I no longer "+
			"need to work to pay off my debt! I think I'll keep working here "+
			"though. Hrm. Here, have this neck pen as a token of my esteem.");
		if(gave) {
			command("say well, I seem to have already given my pen away. Oh well. "+
				"Thanks anayway!");
			return;
		}
		new("/d/nfd/obj/pen")->move(environment());
		message("other_action","The clerk tosses his  pen onto the ground.",
			environment());
		gave = 1;
	}
	::catch_tell(str);
}
