// Maxwell's Underground Mudlib
// Greveck's Triangular Arm Shield
    
inherit "/std/armour";
string right_desc;

void create() {
     ::create();
     set_name("steel shield");
     set("id", ({ "shield","steel shield","right-arm shield" }) );
     set("short", "a cresent steel right-arm shield");
     right_desc = ("This shield is made from pounded steel. The "
     "outer edge of the shield is rounded into a cresent shape, with a row "
     "of steel razor sharp spikes for impaling into an enemy.\nThe inside "
     "curve of the shield is jagged, almost as if it was designed to be "
     "joined with another piece\n");
     set_long(right_desc);
     set_weight(75);
     set("value", 250);
     set_type("shield");
     set_limbs( ({ "right arm"}) );
     set_ac(20);
     set_ac(33,"impaling");      
     set_ac(33,"cutting");                     
     set_ac(33,"crushing"); 
     set_wear("You slide you arm through the steel arm clamp, locking "
     "the right-shield securely on." ); 
     set_remove("You undo the right-shield clamp and pull your arm out.");
     set_material("Dwarven Steel");
     set_property("shield_status","seperated");
     set_property("side","right side");
}
init() {
   ::init();
   add_action("join_shield","join");
   add_action("seperate_shield","seperate");
}
int join_shield(string str){
    if(str == "shield"){
       if( (this_object()->query_property("side")) == "left side"){
          if(!present("right-arm shield")){
             write("You can't join the shield, you don't have the right-arm "
                   "shield!");
             return 1;
          }
          write("You push the two plates together and lock the clamp. The "
                "shield is now a complete circle.");
          return 1;
       }
       if( (this_object()->query_property("side")) == "right side"){
           if(!present("left-arm shield")){
             write("You can't join the shield, you don't have the left-arm "
                   "shield!");
             return 1;
           }
       }
    }
}
int seperate_shield(string str){
    if(str == "shield"){
      if( (this_object()->query_property("shield_status")) == "seperated"
           && (!present("left-arm shield")) ){
        write("The shield is already seperated!");
        return 1;      

      }
   }
}
       



