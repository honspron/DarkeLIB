// Maxwell's Underground Mudlib
// Greveck's Triangular Arm Shield
    
inherit "/std/armour";
string left_desc,full_desc;

void create() {
     ::create();
     set_name("left-arm shield");
     set("id", ({ "steel shield","left-arm shield","shield" }) );
     set("short", "a cresent steel left-arm shield");
     left_desc = ("This shield is made from pounded steel. The "
     "outer edge of the shield is rounded into a cresent shape, with a row "
     "of steel razor sharp spikes for impaling into an enemy.\nThe inside "
     "curve of the shield is jagged, almost as if it was designed to be "
     "joined with another piece\n");
     full_desc = ("The shield is made from pounded steel. The round"
      "outer edge of the shield has a row of razor sharp spikes for "
     "impaling into an ememy.\nThe shield looks like it can be sperated "
     "into two pieces.\n"); 
     set_long(left_desc);
     set_weight(75);
     set("value", 250);
     set_type("shield");
     set_limbs( ({ "left arm"}) );
     set_ac(20);
     set_ac(33,"impaling");      
     set_ac(33,"cutting");                     
     set_ac(33,"crushing"); 
     set_wear("You slide you arm through the steel arm clamp, locking "
     "the left shield securely on." ); 
     set_remove("You undo the left shield clamp and pull your arm out.");
     set_material("Dwarven Steel");
     set_property("shield_status","seperated");
     set_property("side","left side");
}
init() {
   ::init();
   add_action("join_shield","join");
   add_action("seperate_shield","seperate");
}
int join_shield(string str){
    if(str == "shield"){
       if( (this_object()->query_property("side")) == "left side"){
          if( !present("right-arm shield")
              && query_property("shield_status") == "seperated" ){
             write("You can't join the shield, you don't have the "
                  "right-arm shield!");
             return 1;
          }
          if( query_property("shield_status") == "joined" ){
            write("The shield is already joined!");
            return 1;
          }

          (present("right-arm shield"))->remove();
            if(query_worn() != 0)
              this_player()->force_me("remove left-arm shield");
          write("You push the two plates together and lock the clamp. The "
                "shield is now a complete circle.");
          set_long(full_desc);
          set_short("a large steel round shield");
          set_name("round shield");
          set("id", ({ "steel shield","round shield","shield" }) );
          set_limbs(({({"left arm", "right arm"})}));
          set_weight(150);
          set("value", 750);
          set_ac(40);
          set_ac(75,"impaling");      
          set_ac(75,"cutting");                     
          set_ac(75,"crushing"); 
          set_property("shield_status","joined");
          set_wear("You slide you arm through the steel arm clamp, locking "
              "the round shield securely on." ); 
          set_remove("You undo the round shield clamp and pull your arm "
              "out.");
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
      if( (this_object()->query_property("shield_status")) == "seperated"){
        write("The shield is already seperated!");
        return 1;
      }
      write("You unlock the clamp and pull the shield apart into two "
            "seperate arm shields.");
      new("/wizards/maxwell/objects/armour/lashield")->move(this_player());
      new("/wizards/maxwell/objects/armour/rashield")->move(this_player());
      remove();
      return 1;
    }
    
}
       



