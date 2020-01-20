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
   set_weight(400);
   set_value(1500);
   set_wc(35,"cutting");
   set_ac(1);
   set_decay_rate(1500);
   set_quality(5);
   set_auto_critical("plasma E");
//   set_enh_critical(2);
   set_type("two handed blade");
   set_wield_string("You can feel the power of the weapon surround your "
   "hands and arms.");
}
