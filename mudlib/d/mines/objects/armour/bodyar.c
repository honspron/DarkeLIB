//           Maxwell's Underground Mud Library 
//                Dwarven Guardian Bodyarmour    
inherit "/std/armour";

void create() {
    ::create();
    set_name("body-armour");
    set("id", ({ "body-armour","body armour" }) );
    set("short", "molded platinum plate bodyarmour");
    set("long", "This bodyarmour was created by some of the finest "
    "dwarf craftsman. The thick armour is molded and polished to a "
    "bright sheen. A large dragon is painted on the front of the armour.");
    set_weight(200);
    set_value(200);
    set_type("armour");
    set_limbs( ({ "torso" }) );
    set_ac(25);
    set_wear("You strap on the body-armour and tighten the locks.");
}



