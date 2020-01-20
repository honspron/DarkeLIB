//           Maxwell's Underground Mud Library 
//                Dwarven Leather Shirt    
inherit "/std/armour";

void create() {
    ::create();
    set_name("shirt");
    set("id", ({ "leather shirt","shirt" }) );
    set("short", "a Dwarven leather shirt");
    set("long", "This shirt is made from high quality rawhide leather. "
"The seams of the shirt are held together with looped leather string. "
"There are several stains and darkened areas on it from frequent use.\n");
    set_weight(75);
    set_value(100);
    set_type("armour");
    set_limbs( ({ "torso", "right arm", "left arm" }) );
    set_ac(10);
    set_wear("You pull the shirt over your torso and arms." );
}



