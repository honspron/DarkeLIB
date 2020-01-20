//               Steel Breastplate    

inherit "/std/armour";

object player,armour;



void create() {

    ::create();

    set_name("breast-plate");

    set("id", ({ "breast-plate","breastplate","steel breastplate",

                 "steel breast-plate" }) );

    set("short", "molded steel breast-plate");

    set("long", "This steel plate is moulded into massive chest "

"muscles. The sides of the the plate have leather and steel banded straps "

"that wrap around and connect to the back plate.\nA large Dragon is "

"engraved on the front. It's huge claws are crushing a pile of bleached "

"bones.\n");

    set_weight(100);

    set("value", 125);

    set_type("armour");

    set_limbs( ({ "torso" }) );

    set_ac(5);

    set_ac(35,"impaling");      

    set_ac(35,"cutting");                     

    set_ac(35,"crushing"); 

    set_wear("You press the armour against your torso and tighten the "

             "straps." ); 

    set_remove((: delayed_call,"remove_equipment",1:));

    

    set_material("metal/steel");

     armour = this_object();

    

}



void set_caster(object ob) {

  player = ob;

}



void remove_equipment(){

         tell_object(player,"Suddenly the breast plate bursts into blue "

                           "flames and crumbles to ashes!");

        this_object()->remove();

}



int drop() {

  remove_delayed_call("remove_equipment");

  delayed_call("remove_equipment", 3);

  return 0;

}

