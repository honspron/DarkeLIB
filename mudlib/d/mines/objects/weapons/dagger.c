//    Maxwell's Underground Mudlib
//           Dwarven Dagger

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"dagger","crystal dagger"}));
   set_name("dagger");
   set_short("crystal dagger");
   set("long", "This dagger is composed of a sharp crystaline "
       "substance and a handle of pure steel.");
   set_weight(40);
   set("value", 0);
   set_wc(6,"impaling");
   set_ac(2);
   set_quality(3);
   set_type("knife");
   set_parry_bonus(-15);
   set_verb("stab");
   set_throwable(1);
   set_float_value(0.23);
   set_material("crystal");
   set_wield_string("You can feel the balanced pick in your "
   "hands.");
}
