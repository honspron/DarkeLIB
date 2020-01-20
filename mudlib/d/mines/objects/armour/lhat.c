//           Maxwell's Underground Mud Library 
//                Dwarven Leather Hat        
inherit "/std/armour";

void create() {
    ::create();
    set_name("leather hat");
    set("id", ({ "hat","leather hat" }) );
    set("short", "a dirty leather hat");
    set("long", "This is a standard oiled leather hat. The leather is "
    "very dark in some areas because of the humid air inside the mine. ");
    set_weight(18);
    set_value(60);
    set_type("helmet");
    set_limbs( ({ "head" }) );
    set_ac(12);
    set_wear("You pull the hat low over your brow." );
}



