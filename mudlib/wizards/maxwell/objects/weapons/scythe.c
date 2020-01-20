//    Maxwell's Underground Mudlib
//           Darwven Scythe

inherit "/std/weapon";
#include "/adm/include/move.h"

create() {
    ::create();
   set_id(({"scythe"}));
   set_name("scythe");
   set_short("long wooden scythe");
   set("long", "This scythe is made of a long wooden staff and a sharp "
   "steel blade. The staff has a steel spike at bottom.");
   set_weight(300);
   set("value", 225);
   set_wc(65,"cutting");
   set_ac(5);
   set_decay_rate(300);
   set_parry_bonus(-10);
   set_quality(5);
   set_enh_critical(5);
   set_type("two handed polearm");
   set_wield_string("You can feel the perfect balance of the weapon as "
   "you wield it in your hands.");
   set_material("Dwarven Steel");
}
int move(object dest){    
int res;
 if(!living(dest)) return ::move(dest);
 if( living(dest) && this_player()->query_name() == "dravack" &&
     getuid(this_player()) == "maxwellobj" ){
    write("You grab the steel shaft of the axe and feel its "
    "power surge into your hand!");
    return ::move(dest);    
 }   
 else {
  write("You try to grasp the scythe but it burns your hand!");     
  say(this_player()->query_cap_name()+" is burned by the Scythe!");
  return MOVE_NOT_ALLOWED;
    
 }
}
