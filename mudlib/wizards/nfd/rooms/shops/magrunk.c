// /d/nfd/rooms/shops/magrunk
// the shopkeeper of magrunk's

inherit "/std/npc_shop";


void reset() {
   ::reset();
this_object()->set_money("copper",4000);
}
void init() {
	::init();
}

void create() {
   ::create();
   set_name("magrunk");
   set("id", ({"shopkeeper","shop keeper","magrunk","a shopkeeper",
            "a shop keeper"}) );
   set_level( 16 );
   set("short","The shopkeeper Magrunk");
   set("long","This is a strong, well built guy who looks like his life has "+
      "not been the easiest. He appears to be a very shrewd business man "+
      "and not a bad fighter aswell.  However, he strictly prohibits fighting in "+
      "his shop, and he doesn't look like the type you"+
      "'d want to mess with. He is pointing to a sign.");
   set("race","human" );
   set_gender("male");
   set_body_type("human");
   set_overall_ac(65);
   set_languages( ({"common"}) );
   set_lang_prof("yin",9);
   set_lang_prof("farsi",8);
   set_lang_prof("undead",9);
   set_lang_prof("drow",9);
   set("storage room","/d/nfd/rooms/shops/magrunkstorage");
   set("markup",1);
	reset();
}
