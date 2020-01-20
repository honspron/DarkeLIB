inherit "/std/weapon";

create() {
 ::create();
   set_id(({"sword","defender"}));
   set_name("defender");
   set_short("Mithril sword named Defender");
   set("long",
         "This sword was forged by a master craftsman "+
         "and is weighted perfectly.  The metal is pure mithril.");
   set_weight(300);
   set_value(5000);
   set_material("metal/mithril");
   set_wc(25, "cutting");
   set_ac(50);
   set_type("two handed blade");
   set_quality(6);
   set_decay_rate(2000);
   set_verb("shred");
   set_parry_bonus(30);
   set_hit_bonus(10);
}
