//           Maxwell's Underground Mud Library 
//                Dwarven Lowman Vest   
inherit "/std/armour";

void create() {
    ::create();
    set_name("vest");
    set("id", ({ "vest","lowman vest","dwarven lowman vest" }) );
    set("short", "a Dwarven Lowman vest");
    set("long", "This leather and fabric vest was made by the dwarves. "
"It has several large steel buttons and decorative colorful tasels. It "
"looks very comfortable.");
    set_weight(75);
    set_value(100);
    set_type("armour");
    set_limbs( ({ "torso" }) );
    set_ac(13);
    set_wear("You pull the vest over your torso and snap the buttons.");
}



