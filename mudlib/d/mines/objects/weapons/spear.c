//    Maxwell's Underground Mudlib
//           Dwarven Spear

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"spear"}));
   set_name("spear");
   set_short("steel spear");
   set("long", "This spear is made of a strong shaft of steel and "
   "a sharp tempered head. Along the side of the head are several "
   "razor sharp barbs.");
   set_weight(110);
   set_value(130);
   set_wc(20,"impaling");
   set_ac(5);
   set_quality(3);
   set_parry_bonus(-10);
   set_decay_rate(400);
   set_type("two handed polearm");
   set_wield_string("You grip the long spear in your hands.");
   set_verb("stab");
}
