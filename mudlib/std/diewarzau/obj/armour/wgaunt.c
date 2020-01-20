//               Steel Gauntlets  

inherit "/std/armour";

object player;



void create() {

    ::create();

    set_name("gauntlets");

    set("id", ({ "gauntlets","steel gauntlets"}) );

    set("short", "pair of shiny blackened steel gauntlets");

    set("long", "This is a pair of blackened steel gauntlets. You can see "

        "the fine craftsmanship in the seams and plates of the "

        "gauntlets. Encrusted along the ridges are several types "

        "of gems.\n");

    set_weight(30);

    set("value", 1);

    set_type("glove");

   set_limbs( ({ "right hand","left hand" }) );

    set_ac(5);

    set_ac(30,"impaling");      

    set_ac(30,"cutting");                     

    set_ac(30,"crushing"); 

    set_wear("You push your hands into the steel gauntlets." ); 

    set_remove((: delayed_call,"remove_equipment",1:));

    set_material("metal/steel");

    set_property("no save", 1);

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

        tell_object(player,"Suddenly the guantlets burst into blue flames "

                           "and crumble to ashes!");

        this_object()->remove();

}





