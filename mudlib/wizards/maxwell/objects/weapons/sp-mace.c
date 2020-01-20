//    Maxwell's Underground Mudlib
//           Dwarven Spiked Mace

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"club","spiked mace"}));
   set_name("mace");
   set_short("long steel chained mace");
   set("long", "This articulated club is made of a heavy-duty steel shaft "
   "and a long steel-linked chain. Attached to the end of the chain is "
   "a hefty spiked ball.\n");
   set_weight(260);
   set_value(150);
   set_wc(20,"crushing");
   set_ac(5);
   set_quality(3);
   set_type("two handed flail");
   set_verb("smash");
   set_parry_bonus(-20);
   set_wield_string("You grip the study shaft and give the chain a "
   "confident swing.");
   set_material("Dwarven Iron");
}
