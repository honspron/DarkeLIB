/*
   Poison Lore skill.  Enables the player to make poisons from the
   various flora of DarkeMud.
   -Duridian 5/22/96
 
   For an object to be a poison ingredient, it must inherit the
   file /wizards/duridian/poison/poisonous_plant.c
*/
 
#include "/adm/include/clock.h"
#define PATH "/wizards/duridian/poison/plants/"
 
inherit "/std/skills/skill.c";
 
void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(67);
    set_fast_dev_cost(145);
    set_property("no target", 1);
}
 
void info() {
message("help",
"The resins of the various grasses and plants found in the plains "
"can be used to create various potent poisons and toxins.  Use "
"of this skill enables the player to make poisons that can be applied "
"to a weapon.  The maker of poisons will need a plant press to extract "
"the resins and vials in which to store the deadly substances.  The "
"potency of poisons varies with the kind of plants used to create them "
"and with the skill of the maker.  As it is hard on the eyes to search "
"for plants in the plains, the player must rest a while between "
"subsequent searches.",
this_player());
}
 
void skill_func(object from, object at, string arg) {
   object ob;
   int plant_number = 0;
 
   if(!environment(from)->query_terrain() || capitalize((string)
      environment(from)->query_terrain()) != "P") {
         message("info", "You have to be in the plains to use this skill.",
                                                                   from);
         return;
      }
  if((time() - (int)from->query_last_use("poison lore")) / MINUTE < 10) {
      message("info", "You must wait a little longer before using this skill again.",
              from);
      return;
   }
 
   from->set_last_use("poison lore");
   seteuid(geteuid(this_object()));
 
   plant_number = random((int)this_player()->query_skill("poison lore")) +
                        ((int)from->query_stats("intelligence") - 20)/10 +
                        (((int)from->query_skill("perception") - 20)/10) -
                        10 + random(21);
 
   if (plant_number <= 0) {
      message("info", "You find no useful plants.", from);
      return;
   }
 
   switch(plant_number) {
      case 1..5: ob = new(PATH+"purple_grass"); break;
      case 6..10: ob = new(PATH+"yellow_grass"); break;
      case 11..15: ob = new(PATH+"yithki_weeds"); break;
      case 16..20: ob = new(PATH+"pine_needles"); break;
      case 21..25: ob = new(PATH+"jerup_weeds"); break;
      case 26..30: ob = new(PATH+"fulma_leaves"); break;
      case 31..35: ob = new(PATH+"koji_mushrooms"); break;
      case 36..40: ob = new(PATH+"nagasik_leaves"); break;
      case 41..45: ob = new(PATH+"durdin_seeds"); break;
      case 46..50: ob = new(PATH+"marsig_mushrooms"); break;
      case 51..55: ob = new(PATH+"geckin_twigs"); break;
      case 56..60: ob = new(PATH+"jumbu_sprouts"); break;
      case 61..65: ob = new(PATH+"gangus_root"); break;
      case 66..70: ob = new(PATH+"polkin_buds"); break;
      case 71..75: ob = new(PATH+"pixie_winks"); break;
      case 76..80: ob = new(PATH+"lotus_blossoms"); break;
      case 81..85: ob = new(PATH+"faerie_blossoms"); break;
      case 86..90: ob = new(PATH+"blood_root"); break;
      case 91..95: ob = new(PATH+"draco_thorns"); break;
      case 96..1000000: ob = new(PATH+"demon_horns"); break;
      default: write("Poison Lore BUG!  Mail Duridian immediately!"); return; break;
   }
 
   message("info", "You search the ground for a moment and find " +
                   ob->query_short() + ", which you pick up.", from);
   message("info", capitalize((string)from->query_name()) +
           " searches the ground and picks up " + ob->query_short() + ".",
            all_inventory(environment(from)), ({ from }));
 
   if(objectp(ob))
      ob->move(from);
   remove();
   return;
}
