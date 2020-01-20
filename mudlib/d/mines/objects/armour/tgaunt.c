//               Steel Gauntlets  
inherit "/std/armour";


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
    set_ac(15);
    set_ac(15,"impaling");      
    set_ac(15,"cutting");                     
    set_ac(15,"crushing"); 
    set_wear("You push your hands into the steel gauntlets." ); 
    set_remove((: call_out,"remove_equipment",1,this_object():));
    set_material("Blackened Steel");
}
void remove_equipment(){
         write("Suddenly the guantlets burst into blue flames "
               "and crumble to ashes!");
        this_object()->remove();
}


