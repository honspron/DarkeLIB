inherit "/std/weapon";



create() {

  ::create();

  set_id(({"sword","claymore"}));

  set_name("mind-bender");

  set_short("mabril claymore");

  set("long",@TEXT

This is an exquisite two-handed claymore.  While it appears

tto have been forged of pure mabril, the cross piece appears

to have inlayed mithril and intricate scroll work.  The grip

is wrapped in a blue-tinted leather and the pomelstone is

a prominant star saphire.

TEXT

);   

  set_weight(500);

  set_value(15000);

  set_ac(50);

  set_wc(25);

  set_material("metal/mabril");

  set_type("two handed blade");

  set_quality(6);

  set_decay_rate(100);

  set_verb("slash");

  set_parry_bonus(30);

  set_hit_bonus(30);

}

