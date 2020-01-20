//    Maxwell's Underground Mudlib 
//    Gold and Silver Bladed Axe of Montar

inherit "/std/weapon";
 
void create() {
  ::create();
    set_name("Axe of Montar");
    set_id( ({ "axe","gold and silver axe of montar","gold axe",
               "silver axe" }) );
   set_long("This is the famous Dwarven Axe of Montar. It is made of a "
     "razor sharp gold blade, a jagged silver blade and a long leather "
     "wrapped steel shaft. Engraved into the shaft are strange Dwarven "
     "symbols.");
    set_short("Gold and Silver Bladed Axe of Montar"); 
    set_weight(500);
    set_wc(40,"cutting");
    set_wc(40,"impact");
    set_wc(40,"crushing");
    set_quality(5);
    set_value(10000);
    set_type("two handed blade");
    set_wield_string("You wield the Axe of Montar and feel the shaft "
                     "vibrate with internal energy!");
    set_material("a Gold Blade, a Silver Blade and a Dwarven Steel Shaft");   
}

