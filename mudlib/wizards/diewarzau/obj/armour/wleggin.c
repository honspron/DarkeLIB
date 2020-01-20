//               Steel Leggings        

inherit "/std/armour";

object player;



void create() {

    ::create();

    set_name("steel leggings.");

    set("id", ({ "leggings","steal leggings" }) );

    set("short", "pair of dark steel leggings");

    set("long", "These leggings are made from blackened steel that "

"has been fused together with molten metal. The fine craftsmanship "

"is easy to see.\n");

    set_weight(150);

    set("value", 1);

    set_type("pants");

    set_limbs( ({ "left leg","right leg" }) );

    set_ac(15);

    set_ac(15,"impaling");      

    set_ac(15,"cutting");                     

    set_ac(15,"crushing"); 

    set_wear("You put on the steel leggings and strap them tightly.");

    set_remove((: delayed_call,"remove_equipment",1:));

    set_material("metal/steel");

}



void set_caster(object ob) {

  player = ob;

}



int drop() {

  remove_delayed_call("remove_equipment");

  delayed_call("remove_equipment", 3);

  return 0;

}



void remove_equipment(){

        tell_object(player,"Suddenly the leggings burst into blue flames "

                           "and crumble to ashes!");

        this_object()->remove();

}







