//    Maxwell's Underground Mudlib
//           Darwven Pronged Sword

inherit "/std/weapon";
#include <move.h>

create() {
    ::create();
   set_id(({"pronged sword","sword","pronged-blade sword"}));
   set_name("pronged sword");
   set_short("steel pronged-blade sword");
   set("long", "This heavy sword is made from glistening steel that has "
   "been split into two blades near the tip. The prongs are razor sharp "
   "on both sides. A deep blood grove starts at the end of the prong joint "
   "and stretchs down the rest of the blade.");
   set_weight(500);
   set_value(600);
   set_wc(40,"cutting");
   set_parry_bonus(-10);
   set_ac(3);
   set_verb("slash");
   set_decay_rate(300);
   set_quality(5);
   set_enh_critical(2);
   set_type("two handed blade");
   set_material("Dwarven Steel");
   set_wield_string("You grip the hilt of the sword and feel its internal "
   "power flow through your limbs!");
}
int move(object dest){    
int res;
 if(!living(dest)) return ::move(dest);
 if( living(dest) && this_player()->query_name() == "greveck" &&
     getuid(this_player()) == "maxwellobj" ){
    write("You grab the steel shaft of the sword and feel its "
    "power surge into your hand!");
    return ::move(dest);    
 }   
 else {
  write("You try to grasp the sword but it burns your hand!");     
  say(this_player()->query_cap_name()+" is burned by the Scythe!");
  return MOVE_NOT_ALLOWED;
    
 }
}
