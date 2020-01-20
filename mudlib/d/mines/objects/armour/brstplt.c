//           Maxwell's Underground Mud Library 
//                Dwarven Lowman Breastplate    
inherit "/std/armour";

void create() {
    ::create();
    set_name("breast-plate");
    set("id", ({ "breast-plate","breast plate" }) );
    set("short", "molded Dwarven breastplate");
    set("long", "This steel plate is moulded into massive chest "
"muscles. The sides of the the plate have leather and steel banded straps "
"that wrap around and connect to the back plate.\nEngraved on the front "
"is coiled rattlesnake, prepared to strike!");
    set_weight(100);
    set_value(250);
    set_type("armour");
    set_limbs( ({ "torso" }) );
    set_ac(35);

    set_ac(30,"fire");
    set_ac(30,"cold");
    set_ac(30,"plasma");
    set_ac(30,"strike");
    set_ac(30,"vacuum");
    set_ac(20,"electricity");
    set_ac(30,"depression");
    set_ac(30,"disruption");
    set_ac(30,"stress");
    set_ac(30,"holy");
    set_ac(30,"time");
    set_ac(30,"aether");

    set_wear("You strap on the breast-plate and lock it tightly to your "
             "torso.");
}



