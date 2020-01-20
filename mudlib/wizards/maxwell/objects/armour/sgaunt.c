//           Maxwell's Underground Mud Library 
//                Dwarven Steel Gauntlets  
inherit "/std/armour";

void create() {
    ::create();
    set_name("gauntlets");
    set("id", ({ "gauntlets","steel gauntlets"}) );
    set("short", "a pair of steel gauntlets");
    set("long", "This is a pair of steel dwarven gauntlets. You can see "
        "the fine dwarf craftsmanship in the seams and plates of the "
        "gauntlets.\n");
    set_weight(50);
    set_value(130);
    set_type("glove");
    set_limbs( ({ "right hand","left hand" }) );
    set_ac(30);
    set_wear("You pull the steel gauntlets over your hands.");
}



