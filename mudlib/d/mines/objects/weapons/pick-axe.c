//    Maxwell's Underground Mudlib
//           Dwarven Pick

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"pick-axe","axe"}));
   set_name("pick-axe");
   set_short("sharp steel pick-axe");
   set("long", "This pick-axe is made of a strong piece of steel and "
   "a long oak shaft. The left side of the weapon's head is made of a sharp "
   "axe blade while the right side is composed of a long impaling pick.");
   set_weight(180);
   set_value(165);
   set_wc(15,"impaling");
   set_ac(5);
   set_quality(3);
   set_type("two handed polearm");
   set_parry_bonus(-20);
   set_verb("slice");
   set_wield_string("You can feel the balanced pick-axe in your hands.");
   set_material("Dwarven Steel");
}
