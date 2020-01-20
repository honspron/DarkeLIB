#include "/wizards/excelsior/misc/domain.h"

inherit "std/barkeep";

void reset() {
	::reset();
	if (this_object()->query_money("gold") < 1000) this_object()->set_money(
		"gold",1000);
}

void create() {
	::create();
	set_name("barkeep");
	set("id",({"barkeep","barman","barguy"}) );
	set_level( 20 );
	set("short","A nameless barkeep");
	set("long","This nameless fellow is running the South Cape Tavern. He "+
		"is doing a booming business.");
	set("race","human");
	set_gender("male");
	set_body_type("human");
	set_overall_ac( 20 );
	set_combat_chance( 50 );
	add_spell("heal","$ME");
	set_spell_level("heal",5);
	set_skill("melee",90);
	set_skill("attack",90);
	set_skill("prayer",90);
	set_melee_damage( "plasma" );
	set_languages( ({"yin","serra","elvish","common","middle-english","dwarvish",
			"treefolk","undead-tongue","vr'krr"}) );
	set_menu( ({"vodka","wine","coffee","bag of apples","scotch"}),
		({"alcoholic","alcoholic","caffeine","food","alcoholic"}),({100,20,20,50,25}) );
	set_currency("copper");
	set_my_mess( ({ "You down the glass of vodka.",
		"The wine revives your strength.",
		"The coffee sobers you up.",
		"Several apples a day keep many doctors away. Yum yum.",
		"You enjoy scotch." }) );
	set_your_mess( ({"enjoys a glass of vodka.",
		"enjoys some wine.",
		"drinks some yummy coffee.",
		"consumes an entire bag of apples.",
		"drinks good 'ol scotch." }) );
	set_menu_short( ({"A glass of vodka",
		"A glass of wine",
		"A cup of coffee",
		"A bag of shiny red apples",
		"Scotch on the rocks" }) );
	set_menu_long( ({"This vodka looks very strong.",
		"You want to drink this wine.",
		"This coffee will help you sober up.",
		"Ug, these apples are probably good for you.",
		"My scotch is good!" }) );
	set_empty_container( ({ "glass",
		"wine glass",
		"styrofoam cup",
		0,
		"glass" }) );
}

