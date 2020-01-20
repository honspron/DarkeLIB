
/*
   Dance of daggers skill coded for the Thief Guild
   Temporarily increases a player's score in the parry and dodge skills.
   by Duridian

   Thanks to Duridian's good code, a True Strike skill.
   by Tailwind  7/8/99
*/
 
#include "/adm/include/clock.h"
 
inherit "/std/skills/skill.c";
 
void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(35);
    set_fast_dev_cost(75);
    set_property("no target", 1);
}
 
void info() {
message("help",
"Using his lightning fast reflexes, a mercenary can temporarily increase his "
"dexterity for a short time. This enables him to strike true on more blows "
"than he normally would be able to. It is a taxing skill, and may only be used "
"once in a while. ",
this_player());
}
 
void skill_func(object from, object at, string arg) {
  object ob;
  int dex_mod = 0;
  int skill;
  string he_she, his_her, He_She;
 
 
   skill = (int)from->query_skill("true strike");
   if((time() - (int)from->query_last_use("true strike")) < 300/(skill))
    {
    message("info", "You are too tired to use this skill again yet.",
from);
    remove();
    return;
   }
   from->set_last_use("true strike");
   seteuid(geteuid(this_object()));
 
   if(from->query_gender() == "female") {
      he_she = "she";
      He_She = "She";
      his_her = "her";
   }
   else {
      he_she = "he";
      He_She = "He";
      his_her = "his";
   }
 
   message("info", "Using your lightning fast reflexes, you begin to strike with incredible accuracy.", from);
 
   message("info",
from->query_cap_name() + " suddenly looks a lot more fluid, and a heckuva lot more quick.",
        environment(from), ({ from }));
 
   dex_mod = skill/2;
 
   ob = new("/std/spells/shadows/true_shadow");
   ob->start_shadow(from, (5 + skill/4),"You stop striking with such great accuracy.");

// Double check this.

   ob->add_new_stat_bonus("dexterity", dex_mod);
   return;
}
