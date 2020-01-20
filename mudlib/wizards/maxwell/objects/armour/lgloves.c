//           Maxwell's Underground Mud Library 
//                Dwarven Leather Gloves     
inherit "/std/armour";

void create() {
    ::create();
    set_name("gloves");
    set("id", ({ "gloves","leather gloves","pair of leather gloves"}) );
    set("short", "a pair of leather gloves");
    set("long", "This is a pair of leather work gloves. The leather "
        "across the palm is very shiny from being used so much. There "
        "is extra protection for the fingers in this pair, in case the "
        "owner accidently smashed his fingers on something.\n");
    set_weight(20);
    set_value(50);
    set_type("glove");
    set_limbs( ({ "right hand","left hand" }) );
    set_ac(15);
    set_wear("You push your hands into the finely oiled gloves.");
}



