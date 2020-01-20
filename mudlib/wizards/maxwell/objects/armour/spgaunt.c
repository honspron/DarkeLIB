//           Maxwell's Underground Mud Library 
//                Dwarven Spiked Gauntlets  
inherit "/std/armour";

void create() {
    ::create();
    set_name("gauntlets");
    set("id", ({"gauntlets","spiked steel gauntlets","spiked gauntlets"}));
    set("short", "a pair of spiked steel gauntlets");
    set("long", "This is a pair of steel dwarven gauntlets. You can see "
        "the fine dwarf craftsmanship in the seams and plates of the "
        "gauntlets.\nThere is a row of sharp spikes along the knuckles "
        "for punching through an ememy's armour plating.");
    set_weight(50);
    set_value(140);
    set_type("glove");
    set_limbs( ({ "right hand","left hand" }) );
    set_ac(30);

    set_ac(25,"fire");
    set_ac(25,"cold");
    set_ac(25,"plasma");
    set_ac(25,"strike");
    set_ac(25,"vacuum");
    set_ac(25,"electricity");
    set_ac(25,"depression");
    set_ac(25,"disruption");
    set_ac(25,"stress");
    set_ac(25,"holy");
    set_ac(25,"time");
    set_ac(25,"aether");

    set_wear("You pull the gauntlets over your hands.");
}



