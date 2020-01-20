//    Maxwell's Underground Mudlib
//           Dwarven Pick

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"pick"}));
   set_name("pick");
   set_short("steel pick");
   set("long", "This pick is made of a strong piece of steel and "
   "a long oak shaft. The head of the pick is worn down, but still sharp.");
   set_weight(15);
   set_value(110);
   set_wc(12,"impaling");
   set_ac(2);
   set_quality(3);
   set_type("blunt");
   set_parry_bonus(-15);
   set_verb("stab");
   set_wield_string("You can feel the balanced pick in your "
   "hands.");
}
