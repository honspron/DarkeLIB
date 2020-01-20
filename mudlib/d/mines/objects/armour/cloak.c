//           Maxwell's Underground Mud Library 
//                Dwarven Lowman Cloak   
inherit "/std/armour";

void create() {
    ::create();
    set_name("cloak");
    set("id", ({ "cloak","lowman cloak","dwarven lowman cloak" }) );
    set("short", "a Dwarven Lowman cloak");
    set("long", "This large gray cloak is made from some type of sturdy "
         "fabric. It has reinforced seams and a thick drawstring.");
    set_weight(50);
    set_value(75);
    set_type("armour");
    set_limbs( ({ "torso" }) );
    set_ac(7);
    set_wear("You wrap yourself in the cloak.");
}



