//    Maxwell's Underground Mudlib
//           Dwarven Pick-Hammer

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"pick-hammer","pick","hammer"}));
   set_name("pick-hammer");
   set_short("sharp steel pick-hammer");
   set("long", "This pick-hammer is made of a sharp octagonal pick and "
   "a square hammer-head, on a long wooden shaft.\nEngraved into the "
   "hammer head are symbols of the Dwarven Empire..");
   set_weight(160);
   set_value(165);
   set_wc(14,"crushing");
   set_ac(5);
   set_quality(3);
   set_type("blunt");
   set_parry_bonus(-15);
   set_verb("crush");
   set_wield_string("You can feel the balanced pick-hammer in your "
   "hands.");
   set_material("Dwarven Steel");
   set_hit((: call_other,this_object(),"weapon_hit" :));
}
mapping weapon_hit(object target){
   if(random(4)){
     tell_object(target,"You ram the pick-hammer's tip into your attacker!");
     return ([ "impaling" : 4 ]);
   }
   else
     return 0;
}
