// /d/nfd/rooms/shops/cleric

inherit "std/barkeep";

void reset() {
	::reset();
	if (this_object()->query_money("gold") < 3000) this_object()->set_money(
		"gold",8000);
}

void create() {
	::create();
	set_name("clerk");
	set("id",({"shopkeeper","clerk","cleric"}) );
	set_level( 20 );
	set("short","A happy clerk");
	set("long","This happy female clerk is here to help you. 'say shopkeeper, "+
		"help' for info on what she can do. Though it doesn't look that tough, "+
		"if you decide to pick a fight with her your chances aren't that great."+
		" You can 'buy' an item if you want it, perhaps you should look at the "+
		"menu.");
	set("race","human");
	set_gender("female");
	set_body_type("human");
   set_overall_ac(100);
	set_combat_chance( 60 );
	add_spell("heal","$ME");
	set_spell_level("heal",5);
	set_skill("melee",100);
	set_skill("attack",106);
	set_skill("prayer",100);
	set_melee_damage( "vacuum" );
	set_languages( ({"yin","serra","elvish","common","middle-english","dwarvish",
			"treefolk","undead-tongue","vr'krr"}) );
	set_menu( ({"vodka","wine","coffee","bag of apples","a leg of lamb"}),
		({"alcoholic","alcoholic","food","food","food"}),({100,20,20,50,150}) );
	set_currency("gold");
	set_my_mess( ({ "You down the glass of vodka.",
		"The wine revives your strength.",
		"The coffee sobers you up.",
		"Several apples a day keep many doctors away. Yum yum.",
		"You knaw on your leg of lamb." }) );
	set_your_mess( ({"enjoys a glass of vodka.",
		"enjoys some wine.",
		"drinks some yummy coffee.",
		"consumes an entire bag of apples.",
		"knaws on a leg of lamb." }) );
	set_menu_short( ({"A glass of vodka",
		"A glass of wine",
		"A cup of coffee",
		"A bag of shiny red apples",
		"A leg of lamb" }) );
	set_menu_long( ({"This vodka looks very strong.",
		"You want to drink this wine.",
		"This coffee will help you sober up.",
		"Ug, these apples are probably good for you.",
		"This hunk of lamb is good for the non-vegetarian type." }) );
	set_empty_container( ({ "glass",
		"wine glass",
		"styrofoam cup",
		0,
		0 }) );
}

