//    Maxwell's Underground Mudlib 
//    Gold and Silver Bladed Axe of Montar

#include <move.h>
#include "under.h"
inherit "/std/weapon";
 
void create() {
  ::create();
    set_name("Axe of Montar");
    set_id( ({ "axe","gold and silver axe of montar","gold axe",
               "silver axe","montar_quest_object" }) );
   set_long("This is the famous Dwarven Axe of Montar. It is made of a "
     "razor sharp gold blade, a jagged silver blade and a long leather "
     "wrapped wooden shaft. Burnt into the shaft are strange Dwarven "
     "symbols.");
    set_short("Gold and Silver Bladed Axe of Montar"); 
    set_weight(500);
    set_wc(40,"cutting");
    set_wc(40,"impact");
    set_wc(40,"crushing");
    set_quality(5);
    set_value(10000);
    set_type("two handed blade");
    set_wield_string("You wield the Axe of Montar and feel the shaft "
                     "vibrate with internal energy!");
    set_material("a Gold Blade, a Silver Blade and a Steel Shaft");   
}
int move(object dest){    
int res;
string *target;
 if(!living(dest)) return ::move(dest);
 if(dest->is_player() != 1){
   target = explode(file_name(dest),"#");
   if(member_array(UNMON+"bart",target) != -1)
    return ::move(dest);
 }
 if( living(dest) && (member_array("axe of montar",dest->query_quests())
    != -1) && (read_file(UNQST+"axe_owner") == getuid(dest)) ){
    write("You grab the steel shaft of the axe and feel its "
    "power surge into your hand!");
    return ::move(dest);    
 }   
 else {
  write("You try to grasp the axe shaft, but it burns your hand!");     
  say(this_player()->query_cap_name()+" is burned by the Axe!");
  return MOVE_NOT_ALLOWED;
    
 }
}

