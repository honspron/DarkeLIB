//    Maxwell's Underground Mudlib
//           Darwven Longsword

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"longswordr","sword"}));
   set_name("longsword");
   set_short("black longsword");
   set("long", "This longsword is made of a deep black steel-like "
   "substance. The hilt of the sword is made from a light green metal. "
   "Carved into the hilt is some sort of ancient script.");
   set_weight(500);
   set_value(800);
   set_wc(35,"cutting");
   set_parry_bonus(-5);
   set_ac(1);
   set_decay_rate(400);
   set_quality(5);
   set_type("two handed blade");
   set_wield_string("You can feel the power of the weapon surround your "
   "hands and arms.");
}
