inherit "/std/weapon";

create() {
    ::create();
   set_id(({"sword"}));
   set_name("sword");
   set_short("sword");
   set("long", "This is a sword.");
   set_weight(350);
   set_value(100);
   set_wc(35, "cutting");
   set_wc(10, "impaling");
   set_ac(10);
   set_type("blade");
   set_quality(6);
   set_decay_rate(75);
   set_property("enchantment",15);
   set_enh_critical(2);
   set_material("metal/mithril");
   set_wield_string("you wield the sword.");
}
