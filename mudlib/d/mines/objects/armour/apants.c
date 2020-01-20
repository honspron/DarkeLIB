//           Maxwell's Underground Mud Library 
//                Dwarven Armoured Leg PLates        
inherit "/std/armour";

void create() {
    ::create();
    set_name("leg plates");
    set("id", ({ "leg plates","armoured plates","armoured leg plates" }) );
    set("short", "armoured steel leg plates ");
    set("long", "These armoured leg plates are made from high quality "
"dwarven steel. These are normally worn by guards and other types of "
"fighters who want a light weight type of leg armour.\n");
    set_weight(200);
    set("value", 175);
    set_type("pants");
    set_limbs( ({ "left leg","right leg" }) );
    set_ac(20);
    set_wear("You strap on the armoured leg plates.");
}



