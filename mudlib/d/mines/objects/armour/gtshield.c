// Maxwell's Underground Mudlib
// Greveck's Triangular Arm Shield
    
inherit "/std/armour";
string left_side;
void create() {
     ::create();
     set_name("steel shield");
     set("id", ({ "shield","steel shield","left-arm shield" }) );
     set("short", "a cresent steel left-arm shield");
     left_desc = ("This shield is made from pounded steel. The "
     "outer edge of the shield is rounded into a cresent shape, with a row "
     "of steel razor sharp spikes for impaling into an enemy.\nThe inside "
     "curve of the shield is jagged, almost as if it was designed to be "
     "joined with another piece\n");
     full_desc = ("The shield is made from pounded steel. The round"
      "outer edge of the shield has a row of razor sharp spikes for "
     "impaling into an ememy.\nThe shield looks like it can be sperated "
     "into two pieces.\n") 
     set_long(left_side);
     set_weight(150);
     set("value", 1);
     set_type("shield");
     set_limbs( ({ "left arm"}) );
     set_ac(15);
     set_ac(150,"impaling");      
     set_ac(15,"cutting");                     
     set_ac(15,"crushing"); 
     set_wear("You slide you arm through the steel arm clamp, locking "
     "the shield securely on." ); 
     set_remove("You undo the shield clamp and pull your arm out.");
     set_material("Dwarven Steel");
     set_property("shield_status","seperated");
}
init() {
   ::init();
   add_action("join_shield","join");
   add_action("seperate_shield","seperate");
}
int join_shield(string str){
    if(str == "shield"){
       if( (this_object()->query_property("side")) == "left side")
          if(!present("right arm-shield")){
             write("You can't join the shield, you don't have the right-arm "
                   "shield!")
             return 1;
          }
          write("You push the two plates together and lock the clamp. The "
                "shield is now a complete circle.");
          return 1;
       }
       if( (this_object()->query_property("side")) == "right side")
           if(!present("left arm-shield")){
             write("You can't join the shield, you don't have the left-arm "
                   "shield!")
             return 1;
           }
       }
    }
}
int seperate_shield(string str){
    if(str == "shield"){
      if( (this_object()->query_property("shield_status")) == "seperated"){
        write("The shield is already seperated!");
        return 1;
      }
      write("You unlock the clamp and pull the shield apart into two "
            "seperate arm shields.");
            this_object()->set_property("shield_status","seperated");
            return 1;
      }
    }
}
       



