//           Maxwell's Underground Mud Library 
//                Dwarven Leather Gloves     
inherit "/std/armour";

void create() {
    ::create();
    set_name("gloves");
    set("id", ({ "gloves","leather gloves","pair of leather gloves"}) );
    set("short", "leather gloves");
    set("long", "These dark leather gloves are cracked and soiled from "
    "frequent use. ");
    set_weight(60);
    set("value", 95);
    set_type("glove");
   set_limbs( ({ "right hand","left hand" }) );
    set_ac(4);
}



