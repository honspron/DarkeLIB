//           Maxwell's Underground Mud Library 
//                Dwarven Riveted Pants       
inherit "/std/armour";

void create() {
    ::create();
    set_name("riveted pants");
    set("id", ({ "pants","riveted pants" }) );
    set("short", "steel riveted pants");
    set("long", "These pants are made from a strong steel mesh that has "
"hundreds of rivets pinned into it. The rivets have been known to help "
"deflect hits to the armour and spread the shockwave of the blow.\n");
    set_weight(175);
    set_value(150);
    set_type("pants");
    set_limbs( ({ "left leg","right leg" }) );
    set_ac(20);

    set_ac(15,"fire");
    set_ac(15,"cold");
    set_ac(15,"plasma");
    set_ac(15,"strike");
    set_ac(15,"vacuum");
    set_ac(15,"electricity");
    set_ac(15,"depression");
    set_ac(15,"disruption");
    set_ac(15,"stress");
    set_ac(15,"holy");
    set_ac(15,"time");
    set_ac(15,"aether");

    set_wear("You pull on the Dwarven riveted pants." );
}



