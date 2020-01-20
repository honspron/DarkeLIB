//    Maxwell's Underground Mudlib
//           Dwarven Sledgehammer

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"hammer","sledgehammer","sledge"}));
   set_name("sledgehammer");
   set_short("heavy sledgehammer");
   set("long", "This sledgehammer is made of a heavy piece of steel and "
   "a long hard oak shaft. The shaft of the sledge looks greasy and dirty.");
   set_weight(100);
   set_value(115);
   set_wc(15);
   set_ac(1);
   set_quality(3);
   set_parry_bonus(-5);
   set_wc(15,"crushing");
   set_type("blunt");
   set_wield_string("You feel the solid weight of the sledge in your "
   "hand.");
}
