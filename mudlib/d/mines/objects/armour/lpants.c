//           Maxwell's Underground Mud Library 
//                Dwarven Leather Pants        
inherit "/std/armour";

void create() {
    ::create();
    set_name("leather pants.");
    set("id", ({ "pants","leather pants" }) );
    set("short", "a pair of dark leather pants");
    set("long", "This pair of leather pants has been darkened from "
        "frequent use. The seams along the sides are held together by "
        "a small gauge wire. They look sturdy enough to withstand "
        "some abuse.\n");
    set_weight(150);
    set_value(160);
    set_type("pants");
    set_limbs( ({ "left leg","right leg" }) );
    set_ac(15);
    set_wear("You pull the leather pants over your legs." );
}



