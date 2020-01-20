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
   set_weight(150);
   set("value", 150);
   set_wc(20,"impaling");
   set_ac(5);
   set_quality(3);
   set_type("two handed blunt");
   set_parry_bonus(-20);
   set_verb("stab");
   set_wield_string("You can feel the balanced pick-hammer in your "
   "hands.");
   set_material("Dwarven Steel");
}
