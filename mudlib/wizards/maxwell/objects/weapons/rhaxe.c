//    Maxwell's Underground Mudlib
//          Rusty Dwarven Hand Axe

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"axe","hand axe","rusty hand axe"}));
   set_name("hand-axe");
   set_short("large rusty hand axe");
   set("long", "This hand axe is made of a rusty steel blade and a "
       "long steel shaft, wrapped in tattered leather.");
   set_weight(85);
   set_value(0);
   set_wc(8,"cutting");
   set_throwable(1);
   set_ac(3);
   set_parry_bonus(-5);
   set_quality(1);
   set_type("axe");
   set_verb("hack");
   set_throwable(1);
   set_float_value(0.82);
   set_wield_string("You grip the long rusty axe shaft.");
   set_material("steel");
   add_poisoning(50);
}
