//    Maxwell's Underground Mudlib
//           Dwarven Stiletto

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"dagger","stiletto"}));
   set_name("stiletto");
   set_short("sharp blackned steel stiletto");
   set("long", "This wicked weapon is made of a thin blade and a thick "
   "bone handle. A long blood groove is runs along the center of the "
   "blade.\n"
   );
   set_weight(20);
   set_value(100);
   set_wc(4,"impaling");
   set_ac(1);
   set_quality(3);
   set_type("knife");
   set_verb("stab");
   set_wield_string("You grip the thick handle tightly.");
   set_material("Dwarven Steel");
}
