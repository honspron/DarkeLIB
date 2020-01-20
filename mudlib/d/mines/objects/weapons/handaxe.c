//    Maxwell's Underground Mudlib
//           Dwarven hand Axe

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"axe","hand axe"}));
   set_name("hand-axe");
   set_short("small silver hand axe");
   set("long", "This hand axe is made of a sharp silver blade and a "
       "long wooden leather wrapped shaft.");
   set_weight(100);
   set_value(0);
   set_wc(15,"cutting");
   set_throwable(1);
   set_ac(3);
   set_parry_bonus(-5);
   set_quality(3);
   set_type("axe");
   set_parry_bonus(-15);
   set_verb("hack");
   set_throwable(1);
   set_float_value(0.82);
   set_wield_string("You can feel the balanced pick in your "
   "hands.");
}
