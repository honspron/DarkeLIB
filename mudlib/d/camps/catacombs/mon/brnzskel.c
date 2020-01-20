/* Monster coded by Duridian for DarkeMud. */
 
#include "std.h"
inherit MONSTER;
 
void create() {
   ::create();
   set_name("bronze skeleton");
   set("id", ({"skeleton", "bronze skeleton"}) );
   set_level(8);
   set("short", "bronze skeleton");
   set("long",
   "Before you stands a human skeleton whose bones appear to be coated "
   "with bronze.  Its metal frame shines in the faint torchlight.  As "
   "it moves, you hear its metal limbs scrape against each other.  This "
   "creature is obviously the product of very evil magic."
   );
   set("race", "undead");
   set_gender("neuter");
   set_money("silver", random(500)+200);
   set_body_type("human");
   set_emotes(5, ({
                   "The skeleton's bronze bones shine in the torchlight.",
                   "The skeleton turns toward you and watches you carefully.",
                   "The skeleton's bones clang loudly against the stone as it walks about.",
                   }), 0);
   set_achats(30, ({
                    "The skeleton swings violently at empty space.",
                    "The skeleton's bones flash brilliantly as the monster fights.",
                  }) );
}
