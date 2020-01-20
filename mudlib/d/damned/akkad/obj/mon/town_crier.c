/* Town Crier coded by Traer for Darke Domain. */
/* 03-22-99 */
 
#include <std.h>
inherit MONSTER;
#include <move.h>
	object ob;

void create() {
   ::create();
   set_name("town crier");
   set("id", ({"town crier", "crier"}) );
   set_level(100);
   set("short", "Town Crier");
   set("long",
"The town crier has been sent here by the gods.\n"+
"He is currently fairly useless as there is no news to cry.\n"+
"As events unfold, he will bring you the latest happenings.\n"+
"The paper he holds has no value today, but the dwarves have their presses ready.\n"+
"Should any newsworthy events happen, this paper will be scribed\n"+
"and copies will be made available for you to parouse.\n"+
"Please keep an eye out for the latest happenings here.\n"
   );
   set("race", "human");
   set_gender("male");
   set_body_type("human");
set_exp(0);
set_emotes(20, ({
"The crier adjusts his pants.",
                   "The crier gargles with salt-water.",
                   "The crier looks about the area.",
                   "Town crier reads a nearby sign.",
                   "The crier grumbles about the slow dwarves and their slower scribes.",
                   "Town crier spies a bird over head as it loops about.",
          "Town crier says, have you heard about the great walled city?",
          "Sources tell me of a dwarven settlement somewhere in the hills.",
     "Town crier says, Should any events happen, be sure to check in with me!",
     "Town crier says, I would love to give you a paper but alas, no scribes have yet documented any newsworthy events.",
     "Town crier says, Extra! Extra! ooops.. heh, I guess no news has happend yet.. *grumble*",
     "Town crier says, I will be here to keep you informed!",
     "Town crier smiles at you.",
                   }), 0);
set_languages( ({ "Common" }) );
set_lang_prof("common", 10);
   new("/d/damned/akkad/obj/newspaper.c")->move(this_object());
}
