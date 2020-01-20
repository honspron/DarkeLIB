//    Maxwell's Underground Mudlib
//           Dwarven Double Blade Dagger

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"dagger","double dagger","double blade dagger"}));
   set_name("dagger");
   set_short("sharp steel double blade dagger");
   set("long", "This dual bladed weapon is made of two separate daggers "
   "that have been joined together at the handles. This design is very "
   "popular among the rogues, allowing for quicker and more accurate "
   "thrusts.");
   set_weight(40);
   set_value(0);
   set_wc(12,"cutting");
   set_wc(6,"impaling");
   set_throwable(1);
   set_parry_bonus(-15);
   set_ac(5);
   set_quality(3);
   set_type("knife");
   set_verb("stab");
   set_wield_string("You grip the handle and the weapon seems to gleam "
   "brightly.");
   set_material("Dwarven Steel");
}
