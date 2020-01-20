//    Maxwell's Underground Mudlib
//           Dwarven Double Head Axe

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"axe","double-headed axe"}));
   set_name("axe");
   set_short("sharp steel doubled-headed axe");
   set("long", "This large axe is made of a two crescent shaped steel blades "
   "and a long steel shaft. The shaft is wrapped in wire and strips of "
   "leather.");
   set_weight(270);
   set_value(175);
   set_wc(20,"impaling");
   set_ac(5);
   set_quality(3);
   set_type("two handed polearm");
   set_parry_bonus(-20);
   set_verb("slice");
   set_wield_string("You can feel the balanced double-headed axe in your "
   "hands.");
   set_material("Dwarven Steel");
}
