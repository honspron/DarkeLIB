//           Maxwell's Underground Mud Library 
//                Dwarven Steel Helmet       
inherit "/std/armour";

void create() {
    ::create();
    set_name("steel helmet");
    set("id", ({ "helmet","steel helmet" }) );
    set("short", "a sturdy steel helmet");
    set("long", "This steel helmet has small engravings of battle scenes "
       "all over it. It has a leather strap that runs under the "
       "chin and a nose-guard.\n");
    set_weight(15);
    set_value(70);
    set_type("helmet");
    set_limbs( ({ "head" }) );
    set_ac(15);
    set_wear("You pull helmet down over your head." );
}



