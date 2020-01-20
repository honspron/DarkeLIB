//    Maxwell's Underground Mudlib
//           Dwarven Cigar

#include <std.h>
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

string short;
int lit;
create() {
    ::create();
   set_id(({"cigar","dark cigar"}));
   set_name("cigar");
   short = "an expensive dark cigar";
   set_short(short);
   set("long", "This expensive cigar was made by one of the finest "
   "Dwarven companies. The aroma of the high quality tobacco fills your "
   "nose.");
   set_weight(5);
   set_value(0);
   lit = 0;
}
int get() { 
    write("You grab the cigar and roll it between your fingers.");
    return 1;
}
int init(){
    ::init();
    add_action("light_cigar","light");
    add_action("snuff_cigar","snuff");
    add_action("puff_cigar","puff");
    add_action("smoke_cigar","smoke");
}
int smoke_cigar(string str){
     if(str == "cigar" || str == "cigar through eyes"){
       if(lit != 1){
         write("You haven't lit the cigar!");
         return 1;
       }
       if(str == "cigar"){
          write("You inhale deeply and blow a large cloud of smoke out "
          "your nose.");
          say(this_player()->query_cap_name()+" inhales deeply through "
          +this_player()->query_possessive()+" cigar and blows a large "
          "smoke cloud out "+this_player()->query_possessive()+" nose");
       }
       if(str == "cigar through eyes"){
         write("You inhale deeply and close your mouth. Slowly you force "
         "the smoke out of your lungs and increase the pressure until your "
         "eyes bulge out and smoke blows out from under your enlarged "
         "pupils!");
         say(this_player()->query_cap_name()+" inhales deeply on "
         +this_player()->query_possessive()+" cigar.\nSuddenly "
         +this_player()->query_cap_name()+"'s face reddens deeply and "
         +this_player()->query_possessive()+" pupils enlarge as a thick "
         "cloud of smoke flows out from under "
         +this_player()->query_possessive()+" eyes!");
        }
        return 1;
      }

} 
int light_cigar(string str){
    if(str == "cigar"){
     if(lit == 1){
       write("The cigar is already lit!");
       return 1;
     }
     write("You light the cigar and puff lightly on it.");
     say(this_player()->query_cap_name()+" lights a cigar and puffs on it.");     
     this_object()->set_short(short+"<burning>");
     lit = 1; 
     return 1;
    }
}
int puff_cigar(string str){
    if(lit != 1 && str == "cigar"){
      write("You haven't lit the cigar!");
      return 1;
    }
    if(str == "cigar"){
      write("You inhale through the cigar and blow out a thick cloud "
       "of white smoke.");
      say(this_player()->query_cap_name()+" puffs on "+
       this_player()->query_possessive()+" cigar and blows out a large "
       "cloud of dark smoke.");
      return 1;
    }
}
int snuff_cigar(string str){
    if(str == "cigar" || str == "cigar on tongue"){
      if(lit != 1){
        write("The cigar isn't lit!");
        return 1;
      }
      if(str == "cigar on tongue"){
        write("You grind the cigar into your wet saliva and try to act "
        "as macho as possible.");
        say(this_player()->query_cap_name()+" grinds a cigar on "+
        this_player()->query_possessive()+" tongue and snuffs out the "
        "embers.");
        lit = 0;
        this_object()->set_short(short);
        return 1;
      }
      write("You snuff out the glowing embers in the end of the cigar.");
      say(this_player()->query_cap_name()+" snuffs out "
      +this_player()->query_possessive()+" cigar");
      lit = 0;
     this_object()->set_short(short);
     return 1;
    }
}

