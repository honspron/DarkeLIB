//           Maxwell's Underground Mud Library 
//                Dwarven Corduroy Pants        
inherit "/std/armour";

void create() {
    ::create();
    set_name("corduroy pants");
    set("id", ({ "pants","corduroy pants","corduroy" }) );
    set("short", "dark corduroy pants");
    set("long", "These pants are made from some strong fiber. There are "
        "several stains along the length of the leg, but they still look "
        "like reliable protection for the legs.\n");
    set_weight(115);
    set_value(120);
    set_type("pants");
    set_limbs( ({ "left leg","right leg" }) );
    set_ac(10);
    set_wear("You slide your legs into the comfortable corduroy pants.");
}



