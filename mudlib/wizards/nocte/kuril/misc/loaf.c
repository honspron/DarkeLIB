inherit "/std/food";

void create() {
  ::create();
  set_name("loaf of bread");
  set_my_mess("The bread just melts in your mouth.");
  set_id( ({ "bread", "loaf", "loaf of bread" }) );
  set_short("A loaf of bread");
  set_strength(30);
  set_long("The loaf of bread has been baked with care and attention.");
  set_weight(5);
  set_float_value(0.74);
  return;
}

