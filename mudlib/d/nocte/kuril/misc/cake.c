inherit "/std/food";

void create() {
  ::create();
  set_name("sweet cake");
  set_my_mess("The cake is yummy for your tummy."
	"morsel.");
  set_id( ({ "cake", "sweet cake" }) );
  set_short("A sweet pastry cake");
  set_strength(12);
  set_long("Each has been baked individually with an eye for perfection.");
  set_weight(3);
  set_float_value(0.50);
  return;
}

