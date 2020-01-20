//           Maxwell's Underground Mud Library 
//                Dwarven Leather Gloves     
inherit "/std/armour";

void create() {
    ::create();
    set_name("gloves");
    set("id", ({ "gloves","leather gloves","pair of leather gloves"}) );
    set("short", "dirty pair of leather gloves");
    set("long", "these leather gloves have been used a lot. ");
    set_weight(60);
    set("value", 95);
    set_type("glove");
   set_limbs( ({ ({ "both hands" }), ({"first branch",
    "second branch", "third branch", "fourth branch" }) }));
    set_ac(4);
}



