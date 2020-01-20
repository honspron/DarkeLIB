//           Maxwell's Underground Mud Library 
//                Dwarven Bandanna        
inherit "/std/armour";

void create() {
    ::create();
    set_name("cloth bandanna");
    set("id", ({ "bandanna","cloth bandanna" }) );
    set("short", "a dirty cloth bandanna");
    set("long", "This is a colorful sweat stained bandana. Many Dwarf "
        "miners wear these to keep the sweat out of their eyes. "
        "This one is quite dirty from use.");
    set_weight(10);
    set_value(25);
    set_type("helmet");
    set_limbs( ({ "head" }) );
    set_ac(8);
    set_wear("You tie the colorful bandanna around your head." );
}



