//               Steel Helmet       

inherit "/std/armour";

object player;



void create() {

    ::create();

    set_name("blackened steel helmet");

    set("id", ({ "helmet","steel helmet" }) );

    set("short", "sturdy steel helmet");

    set("long", "This helmet is made from shiny blackened steel. "

"There is a gold band that wraps around the side and flows down onto the "

"nose-guard.\n");

    set_weight(15);

    set("value", 1);

    set_type("helmet");

    set_limbs( ({ "head" }) );

    set_ac(10);

    set_ac(10,"impaling");      

    set_ac(10,"cutting");                     

    set_ac(10,"crushing");        

    set_wear("You pull the black helmet down over your head." ); 

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

        tell_object(player,"Suddenly the helmet bursts into blue flames "

                           "and crumbles to ashes!");

        this_object()->remove();

}







