//    Maxwell's Underground Mudlib
//           Darwven Longsword

inherit "/std/weapon";
#include <move.h>

create() {
    ::create();
   set_id(({"war-hammer","dwarven war-hammer","hammer","war hammer"}));
   set_name("war-hammer");
   set_short("steel war-hammer");
   set("long", "This steel war-hammer is made of the finest dwarven steel. "
   "The staff is perfectly balanced with the blunt head and the spiked "
   "blade. Engraved on the steel shaft are phrases of ancient Dwarven "
   "script.");
   set_weight(400);
   set_value(500);
   set_wc(65,"crushing");
   set_ac(5);
   set_decay_rate(300);
   set_parry_bonus(-30);
   set_quality(5);
   set_enh_critical(5);
   set_type("two handed blunt");
   set_wield_string("You can feel the power of the weapon surround your "
   "hands and arms.");
   set_material("Dwarven Steel");
}
int move(object dest){    
int res; 
 if(!living(dest)) return ::move(dest);
 if( living(dest) && this_player()->query_name() == "frenish" &&
     getuid(this_player()) == "maxwellobj" ){
    write("You grab the steel shaft of the hammer and feel its "
    "power surge into your hand!");
    return ::move(dest);    
 }   
 else {
  write("You try to grasp the hammer but it burns your hand!");     
  say(this_player()->query_cap_name()+" is burned by the Hammer!");
  return MOVE_NOT_ALLOWED;
    
 }
}
