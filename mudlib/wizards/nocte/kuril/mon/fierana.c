#include <nevin.h>
inherit "/std/barkeep";

create() {
    	::create();
   	set_name("fierana");
    	set_id( ({ "waitress", "fierana", "kuril mob" }) );
    	set_short("Fierana the restaurant waitress");
   	set("aggressive", 0);
  	set_level(10);
    	set_long("She is ready to take your order.\n");
   	set_gender("female");
   	set("race", "human");
	set_max_hp(750);
   	set_hp(750);
   	add_money("silver", 100 + random(50));
   	set_skill("melee",90);
    	set_body_type("human");
    	set_currency("silver");
	set_languages( ({"common"}) );
    	set_menu(
		({ "liquor", "feathers", "ears", "egg", "embryos" }),
		({ "drink_in", "dine_in", "dine_in", "food", "dine_in" }),
		({ 30, 13, 20, 25, 17})
   	 );
    	set_my_mess( ({
		"Hmmm, this doesn't taste so BBAAAAAAAAAAAAAADDDDDD!!!!!!!",
		"They crunch as you chew them.",
		"A little bit on the chewy side, but still satisfying.",
		"A horid smell fills as the room as you crack it open, but it actually tastes very good.",
		"They slide down your throat as you eat them one by one."
	}) );
   	set_your_mess( ({
		"staggers from a shot of darkegrass liquor.",
		"crunches on some fried seraph feathers.",
		"rips apart some elf ears...how disgusting!",
		"consumes a huge egg right before your eyes.",
		"slides some embyros down " +query_possessive()+ " throat."
    	}) );
    	set_menu_short( ({
		"A shot of darkegrass liquor",
		"A bowl of fried seraph feathers",
		"A plate of barbequed elf ears",
		"A steamed roc egg",
		"A plate of kraken embryos"
	}) );
    	set_menu_long( ({
		"The liquor is darke and syrupy.",
		"The bowl of feathers has been fried perfectly brown.",
		"You can hardly recognize that the pieces of flesh before you once belonged to an elf.",
		"With a spotted surface, the egg is almost the size of your head.",
		"A clear gelatinous fluid surrounds the embyros in suspension."
	}) );
}

void catch_tell(string str) {
	string a;
	
	if(sscanf(str, "%s enters.", a) == 1) {
		call_out("greet_player", 1, a);
	}
}

void greet_player(string player) {
	force_me("speak common");
	force_me("say Good day to you, read the menu to find out what we "
		"serve here at the Raking Claw.");
}
