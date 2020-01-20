//    Maxwell's Underground Mudlib
//           Dwarven Spiked Club

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"club","spiked club"}));
   set_name("club");
   set_short("long wooden spiked club");
   set("long", "This composite club is made of thick hardwood and a spiked "
   "head. Long nails are impeded into the wood, wrapped with wire.\n"
   );
   set_weight(100);
   set_value(145);
   set_wc(18,"crushing");
   set_ac(5);
   set_quality(3);
   set_type("blunt");
   set_verb("pound");
   set_parry_bonus(-6);
   set_wield_string("You grip the thick wooden handle tightly.");
   set_material("Dwarven Hardwood");
}
