/*
   Dance of daggers skill coded for the Thief Guild
   Temporarily increases a player's score in the parry and dodge skills.
   by Duridian
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
"Through the use of his ability to move fluidly and elegantly, the "
"dagger dancer can enable himself to better outfox his opponents in "
"battle.  This skill allows the player to temporarily increase his "
"scores in the parry and dodge skills.  However, use of the dance of "
"daggers skill forces the dancer to use a great deal of energy.  Therefore, "
"this skill may only be used once in a while.",
this_player());
}
 
void skill_func(object from, object at, string arg) {
  object ob;
  int parry_mod = 0;
  int dodge_mod = 0;
  int attack_mod = 0;
  int skill;
  string he_she, his_her, He_She;
 
 
   skill = (int)from->query_skill("dance of daggers");
   if((time() - (int)from->query_last_use("dance of daggers")) < 3600/(skill/10))
    {
    message("info", "You are too tired to use this skill again yet.",
from);
    remove();
    return;
   }   
   from->set_last_use("dance of daggers");
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
 
   message("info", "%^BOLD%^%^CYAN%^Concentrating intensely, you force your "+
"body to produce mass amounts of adrenaline.  Your whole body seems to move "+
"more quickly and fluidly, bringing a grin to your face as those around you "+
"look on in disbelief.", from);
 
   message("info",
from->query_cap_name() + "'s breathing increases and "+his_her+" body shakes "+
"slightly as adrenaline pours into "+his_her+" veins.  "+
from->query_cap_name()+" seems to be moving more quickly and fluidly, "+
his_her+" weapon becoming nothing but a blur in front of you as "+he_she+
" employs his dance of the daggers skill.",
        environment(from), ({ from }));
 
   parry_mod = skill/4;
   dodge_mod = skill/4;
   attack_mod = -15;
 
   ob = new("/std/spells/shadows/skill_shadow");
   ob->start_shadow(from, (5 + skill/5 + random(skill/3))*3,
"%^BOLD%^%^GREEN%^Your body's metabolism slows down to its normal rate "+
        "and you stop moving quite so quickly.");
   ob->add_new_skill_bonus("parry", parry_mod);
   ob->add_new_skill_bonus("dodge", dodge_mod);
   ob->add_new_skill_bonus("attack", attack_mod);
   return;
}
 
