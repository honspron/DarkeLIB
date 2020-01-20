//           Maxwell's Underground Mud Library 
//                Dwarven Leather Leg Guards       
inherit "/std/armour";

void create() {
    ::create();
    set_name("leather leg guards");
    set("id", ({ "leather leg guards","leather guards","leg guards" }) );
    set("short", "a pair of dark leather leg guards");
    set("long", "This is a pair of leather leg guards. The dwarf miners "
        "wear these to work with the stones. The guards protect their "
        "legs while they brace the rocks and loosen the gems.\n");
    set_weight(150);
    set("value", 120);
    set_type("pants");
    set_limbs( ({ "left leg","right leg" }) );
    set_ac(7);
    set_wear("You strap on the leather leg guards." );
}



