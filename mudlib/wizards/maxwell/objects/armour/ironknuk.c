//           Maxwell's Underground Mud Library 
//                Dwarven Iron Knuckles
inherit "/std/armour";

void create() {
    ::create();
    set_name("iron knuckle");
    set("id", ({ "knuckle","iron knucke"}) );
    set("short", "an iron knuckle");
    set("long", "This is a standard dwarven iron knuckle. Mostly used "
        "by the lower classes of dwarves in street and bar brawls.\nYou "
        "can see several scatches along the edge that suggests these "
        "beauties have busted many bones.\nThis is designed for a "
        "right handed fighter.");
    set_weight(15);
    set("value", 30);
    set_type("glove");
   set_limbs( ({ "right hand" }) );
    set_ac(5);
}



