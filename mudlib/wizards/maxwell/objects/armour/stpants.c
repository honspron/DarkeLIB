//           Maxwell's Underground Mud Library 
//                Dwarven Steel Plated Pants        
inherit "/std/armour";

void create() {
    ::create();
    set_name("steel pants");
    set("id", ({ "pants","steel plated pants","plated pants" }) );
    set("short", "dark steel plated pants");
    set("long", "These steel jointed pants are made from an underlayer "
        "of steel mesh and an outer plating of steel. The plates of steel "
        "have script engraved into them and other designs.\n");
    set_weight(200);
    set_value(175);
    set_type("pants");
    set_limbs( ({ "left leg","right leg" }) );
    set_ac(20);
    set_wear("You pull the steel mesh plated pants on your legs.");
}



