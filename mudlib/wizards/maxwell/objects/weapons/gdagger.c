//    Maxwell's Underground Mudlib
//           Guard's Dwarven Dagger

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"dagger","guard dagger"}));
   set_name("dagger");
   set_short("blackened steel dagger");
   set("long", "This dagger is composed of sharp steel "
       "and has a handle of pure gold.");
   set_weight(40);
   set_value(0);
   set_wc(6,"impaling");
   set_ac(2);
   set_quality(3);
   set_type("knife");
   set_parry_bonus(-15);
   set_verb("stab");
   set_throwable(1);
   set_float_value(0.23);
   set_material("Steel & Gold");
   set_wield_string("You can feel the balanced dagger in your "
   "hands.");
}
