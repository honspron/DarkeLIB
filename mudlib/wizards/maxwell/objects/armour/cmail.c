//           Maxwell's Underground Mud Library 
//                Dwarven Chain-Mail    
inherit "/std/armour";

void create() {
    ::create();
    set_name("chain-mail");
    set("id", ({ "chain-mail","chain mail" }) );
    set("short", "dwarven chain-mail");
    set("long", "This is a standard issue Dwarven Chainmail. Designed for "
"maximun protection and light weight. All the links have small gold "
"clasps to hold them together.");
    set_weight(230);
    set_value(175);
    set_type("armour");
    set_limbs( ({ "torso", "right arm", "left arm" }) );
    set_ac(23);
    set_wear("You pull the chainmail over your torso and arms." );
}



