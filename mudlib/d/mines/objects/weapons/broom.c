//    Maxwell's Underground Mudlib
//           Dwarven Broom

inherit "/std/weapon";

create() {
    ::create();
   set_id(({"broom","wooden broom"}));
   set_name("wooden broom");
   set_short("wooden broom");
   set("long", "This wooden broom looks like it would be useful for "
   "cleaning up messes.");
   set_weight(20);
   set_value(50);
   set_wc(2, "crushing");
   set_quality(3);
   set_type("blunt");
   set_material("Dwarven Oak and Field Straw");
   set_wield_string("You grab the broom and hope it will be enough.");
}
