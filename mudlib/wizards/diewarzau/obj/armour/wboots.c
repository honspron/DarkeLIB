//                  Amoured Boots        

inherit "/std/armour";

object player;



void create() {

     ::create();

     set_name("steel boots");

     set("id", ({ "boots","steel boots" }) );

     set("short", "pair of pointed steel boots");

     set("long", "These shiny black boots are made from rolled steel. The "

"heal has a plate joint that provides extra protection for the ankles.\n"

"Along the front of the boot are razor sharp blades for cutting.\n");

     set_weight(50);

     set("value", 1);

     set_type("boot");

     set_limbs( ({ "left foot","right foot" }) );

     set_ac(5);

     set_ac(30,"impaling");      

     set_ac(30,"cutting");                     

     set_ac(30,"crushing"); 

     set_wear("You pull the armoured boots onto your feet." ); 

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

        tell_object(player,"Suddenly the boots burst into blue flames "

                           "and crumble to ashes!");

        this_object()->remove();

}







