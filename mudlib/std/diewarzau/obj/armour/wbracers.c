//                  Amoured Boots        

inherit "/std/armour";

object player;



void create() {

     ::create();

     set_name("steel bracers");

     set("id", ({ "bracers","steel bracers" }) );

     set("short", "pair of rounded steel bracers");

     set("long", "These shiny black bracers are made from rounded steel. "

                 "The outer edge of the bracer has a engraved groove.\n");

     set_weight(50);

     set("value", 1);

     set_type("bracer");

     set_limbs( ({ "left arm","right arm" }) );

     set_ac(5);

     set_ac(30,"impaling");      

     set_ac(30,"cutting");                     

     set_ac(30,"crushing"); 

     set_wear("You place the steel bracers on your arms." ); 

    set_material("metal/steel");

     set_remove((: delayed_call,"remove_equipment",1:));

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

        tell_object(player,"Suddenly the bracers burst into blue flames "

                           "and crumble to ashes!");

        this_object()->remove();

}







