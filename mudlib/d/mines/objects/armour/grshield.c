// Maxwell's Underground Mudlib
// Greveck's Round Arm Shield
    
inherit "/std/armour";

void create() {
     ::create();
     set_name("steel shield");
     set("id", ({ "shield","steel shield" }) );
     set("short", "a round steel arm-shield");
     set("long", "This arm-shield is made from pounded steel. Along the "
     "outer edge of the shield is a row of steel razor sharp spikes for "
     "impaling into an enemy.\nThis shield was designed to be worn on "
     "the left arm");
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

}



