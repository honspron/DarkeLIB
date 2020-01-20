//           Maxwell's Underground Mud Library 
//                Dwarven Spike Steel Helmet       
inherit "/std/armour";

void create() {
    ::create();
    set_name("spiked helmet");
    set("id", ({ "helmet","spiked helmet","steel spiked helmet" }) );
    set("short", "a steel spiked helmet");
    set("long", "This steel helmet has a long row of razor sharp spikes "
       "on it. The spikes would be quite devastating if used to head-butt "
       "the attacker.\n");
    set_weight(20);
    set_value(75);
    set_type("helmet");
    set_limbs( ({ "head" }) );
    set_ac(15);
    set_wear("You pull spiked helmet down over your head." );
}



