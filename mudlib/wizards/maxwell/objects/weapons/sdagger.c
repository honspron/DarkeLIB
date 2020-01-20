//    Maxwell's Underground Mudlib
//           Dwarven Crystal Dagger

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"dagger","dwarven dagger"}));
   set_name("dagger");
   set_short("steel dwarven dagger");
   set("long", "This dagger is composed of strong forged steel. The long "
   "blade has a deep blood groove carved into it. Definitely a nasty "
   "weapon for people who like to make others suffer.");
   set_weight(40);
   set_value(0);
   set_wc(7,"impaling");
   set_ac(2);
   set_quality(3);
   set_type("knife");
   set_parry_bonus(-15);
   set_verb("stab");
   set_throwable(1);
   set_float_value(0.23);
   set_material("Dwarven Steel");
   set_wield_string("You wield the sharp dwarven dagger.");
}
