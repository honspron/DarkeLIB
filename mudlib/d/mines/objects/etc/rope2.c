//    Maxwell's Underground Mudlib 
//       Rope for Entrance into Temple

#include <std.h>
#include <under.h>
inherit OBJECT;

int rope_tied,rope_in_position;
string *rope_target,*target_tie,*rope_dest;
object endrope;

void create() {
  ::create();
    set_name("rope");
    set_id( ({ "rope","fiber rope" }) );
    set_short("a thick braided rope" );
    set_long("The thick rope is made from three strong strands of metals."
" Within the braids you can see wraps of gold,silver and steel wire. The "
"rope almost seems to glow slightly. It bends and coils easily as if "
"it had been climbed,tied,untied and thrown frequently.");
    set_weight(20);
    set_value(30);
    rope_target = ({});
    target_tie = ({});
    rope_dest = ({});
}
void init() {
    ::init();
    add_action("throw_rope", "throw");
    add_action("tie_rope","tie");
    add_action("untie_rope","untie");
    add_action("climb_rope","climb");
}
int climb_rope(string str){
string climb_dir,name;
object here;
int pos;
    here = environment(this_object());
    if(here->is_player())
       here = environment(here);
//Config 1 for Room
    if(here = (find_object(UNDER+"dm33")) ){
      rope_target = ({"hole"});
      target_tie  = ({"anchor","bolt"});
      rope_dest   = ({(UNDER+"dm33"),(UNDER+"dm41"),"down"});
    }
    if(str == "rope"){
       if(rope_in_position == 1){
         pos = member_array((file_name(here)),rope_dest);
         if(pos != -1){
           write("You climb "+rope_dest[pos+2]+" the rope.");
           say(this_player()->query_cap_name()+" climbs "+rope_dest[pos+2]
               +" the rope.");
           tell_room(rope_dest[pos+1],this_player()->query_cap_name()+
                     " climbs down on the rope and lands on the floor.");
           this_player()->move(rope_dest[pos+1]);
           return 1;
         }
       }       
       write("The rope isn't ready to be climbed.");
       return 1;       
    }
}
int untie_rope(string str){
    if(str == "rope"){
      if(rope_tied == 1){
         write("You untie the rope and coil it into a bundle.");
    set_long("The thick rope is made from three strong strands of metals."
" Within the braids you can see wraps of gold,silver and steel wire. The "
"rope almost seems to glow slightly.");
         rope_tied = 0;
         rope_in_position = 0;
         if(endrope != 0){
           tell_room(environment(endrope),"Someone pulls the rope up!");
           endrope->remove();
         }
         return 1;
      }
      else {
        write("The rope isn't tied to anything!");
        return 1;
      }
   }
}        
int tie_rope(string str){
object here;
string tie_object,tie_target;

    here = environment(this_object());
    if(here->is_player())
       here = environment(here);
//Config 1 for Room
    if(here == (find_object(UNDER+"dm33")) ){
      rope_target = ({"hole"});
      target_tie  = ({"anchor","bolt"});
      rope_dest   = ({(UNDER+"dm33"),(UNDER+"dm41"),"down"});
    }
    if(str == "rope"){
      write("Tie rope on what?");
      return 1;
    }
    if(str != 0){
     sscanf(str,"%s on %s",tie_object,tie_target);
    {
     if(tie_object == "rope"){    
       if(rope_tied != 1){
        if( (member_array((file_name(here)),rope_dest)) == 0 &&
             (member_array(tie_target,target_tie)) != -1 ){
          write("You tie the rope to the "+tie_target);
          say(this_player()->query_cap_name()+" ties a rope to the "
             +tie_target);
             rope_tied = 1;
          set_long(this_object()->query_long()+"\nThe rope is tied to a "
             +tie_target);
             this_object()->move(here);
             return 1;
        }
        else {
           write("Tying the rope there would be useless.");
           return 1;
        }
      }
      else {
        write("The rope is already tied to something!");
        return 1;
      }
     }
    }
   }
}
int throw_rope(string str){
object here;
string throwing_object,throwing_target,pattern,dest;
    here = environment(this_object());
    if(here->is_player())
       here = environment(here);
//Config 1 for Room
    if(here = (find_object(UNDER+"dm33")) ){
      rope_target = ({"hole"});
      target_tie  = ({"anchor","bolt"});
       rope_dest = ({UNDER+"dm33",
                      UNDER+"dm41","down"});
    }
    if(str == "rope"){
      write("Throw rope at what?");
      return 1;
    }
   if(str != 0){
    sscanf(str,"%s at %s",throwing_object,throwing_target);
    {
      if(throwing_object == "rope"){
        if(rope_in_position != 1){
          if( (member_array(throwing_target,rope_target)) != -1){
            write("You throw the rope at the "+throwing_target);
            say(this_player()->query_cap_name()+" throws a rope at the "
             +throwing_target);
           //If the target has a tie off point
            if( (sizeof(target_tie)) != 0){
               //Check if rope is tied
               if(rope_tied == 1){
                 write("The rope drops into the "+throwing_target+" and "
                    "hangs loosely");
                 say("The rope drops into the "+throwing_target+ " and "
                     +this_player()->query_cap_name()+" waits for it to "
                    "fall into place.");
                 set_long(this_object()->query_long()+"\nThe rope is "
                        "hanging loosely in a "+throwing_target );
                 rope_in_position = 1;
                 this_object()->move(here);  
                  endrope = new(UNETC+"erope");
                 endrope->move(rope_dest[1]);
                 endrope->set_property("climb_dir","up");
                 endrope->set_property("climb_dest",(rope_dest[0]));
                 tell_room(environment(endrope),"A length of rope drops "
                 "in from above!");
                 return 1;
               } 
               //Rope is not tied so display message and remove
               else {
                 write("You wait expectingly as the rope drops out of "
                       "sight.\nHmm..maybe you should have tied it off "
                       "before you did that?");
                 say(this_player()->query_cap_name()+" waits expectingly "
                     "as the rope falls out of sight.");
                 remove();
                 return 1;            
               }
            }
            //Display this message if the rope has no tie off point  
            else {
               write("The rope drops into the "+throwing_target+" and "
                    "hangs loosely");
               say(this_player()->query_cap_name()+" throws the rope into "
                  "the "+throwing_target+" and waits as it slides into "
                  "place.");
               set_long(this_object()->query_long()+"\nThe rope is hanging"
                  "loosely in a "+throwing_target);
               rope_in_position = 1;
               this_object()->move(here);  
                 endrope = new(UNETC+"erope");
               endrope->set_property("climb_dir",rope_dest[3]);
               endrope->set_property("climb_dest",(rope_dest[1]));
               endrope->move(rope_dest[2]);
               return 1;
            }
          }
        //Display this message if the player was throwing at !target
          else {
           write("Throwing a rope there wouldn't help much.");
           return 1;
          }
        }
        //Display If Rope has been thrown and player tries to throw again
        else {
         write("The rope has already been thrown!");
         return 1;
        }        
      }
    }
  }
}
int get(){
    if(rope_tied == 1){
       write("The rope is tied to something!");
       return 0;
    }
    else
       return 1;
}

   

