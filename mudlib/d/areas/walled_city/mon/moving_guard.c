/* Standard monster modified by Traer for dwarf camp. */
#include "../walled_city.h"
#include <std.h>
inherit MONSTER;
 
void create() {
   ::create();
   set_name("guard");
   set("id", ({"dwarf guard", "guard", "dwarf"}) );
   set_level(14+random(3));
   set("short", "dwarf city guard");
   set("long", "This is a big, burly dwarven guard. He smells of rotten flesh and bad hygene."
   );
   set("race", "dwarf");
   set_gender("male");
   set_alignment(-150);
   set_money("silver", random(50)+150);
   set_body_type("human");
   set_wielding_limbs( ({"right hand", "left hand"}) );
   set_emotes(5,
                ({
                "The guard eyes you suspiciously.",
                "The guard shifts his position.",
                "The guard checks his mace.",
                "The guard adjusts his shield.",
                "The guard stands at attention.",
		"The guard grumbles unintelligbly about dragons.",
                }), 0);
   set_achats(30,
                ({
                  "The guard screams a battle cry!",
                  "The guard swings his mace wildly.",
                  "The guard grits his teeth in pain.",
                  "The guard foams at the mouth.",
                }) );

   new(WEAP+"mace")->move(this_object());
   new(ARMOR+"chainmal")->move(this_object());
   new(ARMOR+"shield")->move(this_object());
   new(ARMOR+"helmet")->move(this_object());
   new(ARMOR+"boots")->move(this_object());
   force_me("wield mace in right hand");
   force_me("wear chainmail");
   force_me("wear shield on left hand");
   force_me("wear helmet");
   force_me("wear boots");

	set_moving(1); 
	set_speed(60);
}
 
void catch_tell(string str) {
   string a, b;
   object ob1;
   if(sscanf(str, "%s attacks %s", a, b) == 2) {
      a = lower_case(a);
      ob1 = present(a, environment(this_object()));
      if(ob1) {
         if(interact("guard", b)) {
            ob1->add_follower(this_object());
            force_me("kill "+a);
            return;
         }
      }
   }   
}
 
