inherit "/std/barkeep";

create() {
  ::create();
  set_name("golg");
  set_id( ({ "golg", "tavern keeper" }) );
  set_short("Golg, the Tavern Keeper");
  set("aggressive", 0);
   set_property("enhance criticals", -10);
  set_level(13);
  set_hp(200000);
  set_max_hp(200000);
  set_exp(600000);
  set_long(@TEXT
Golg is a friendly looking dwarf of middle age.  He wears
a coarse-woven apron over a hairshirt.  He looks at you with
a smile while cleaning a glass.
TEXT
);
   set_gender("male");
   set("race", "dwarf");
   add_money("platinum", random(200));
   set_property("melee damage", ([ "crushing" : 99]));  
   set_skill("melee",220);
   set_skill("elementalism", 175);
   set_spell_level("elemental storm", 6);
   add_spell("elemental storm", "");
   set_combat_chance(80);
   set_body_type("human");
   set_currency("silver");
   set_menu( ({
        "ale", 
        "mead", 
        "whiskey", 
        "bread", 
        "mutton", 
        "steak",
        }),({ 
        "alcoholic", 
        "drink_in", 
        "drink_in", 
        "food", 
        "dine_in", 
        "dine_in",
        }),({ 
        5, 10, 15,
        6, 11, 16,
        }) );
    set_my_mess(
	({
	"The ale is smooth with a hoppy aftertaste.\n",
	"The mead is pleasantly sweet.\n",
	"So smooth!\n",
	"The bread is soft and tasty.\n",
	"The mutton is moist and tender.\n",
	"With little exception, this is one of the best steaks you've ever had.\n"
	})
    );
    set_your_mess(
	({
	"chugs a mug of ale.\n",
	"quaffs a tankard of mead.\n",
	"throws back a shot of whiskey.\n",
	"eats a loaf of bread.\n",
	"eats a leg of mutton.\n",
	"eats a dragon steak.\n"
    	})
    );
    set_menu_short(
	({
	"A mug of ale",
	"A tankard of mead",
	"A shot of single malt whiskey",
	"A loaf of bread",
	"A leg of mutton",
	"A dragon steak",
	})
    );
    set_menu_long(
	({
	"The ale is brown with a thick head.\n",
	"The mead is honey golden and looks quite tasty.\n",
	"The whiskey smells strong and well-made.\n",
  "The loaf is freshly baked by Golg's wife.\n",
	"This is a juicy leg of mutton.\n",
  "This is a huge, very choice cut of USDA Choice Dragon!\n",
    }) );
}
int query_num_rounds() { return 3; }

string query_element() { return "vacid"; }
