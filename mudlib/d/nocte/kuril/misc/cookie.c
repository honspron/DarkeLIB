inherit "/std/food";

void create() {
  ::create();
  set_name("sugar cookie");
  set_my_mess("The sugar cookie melts in your mouth as you eat each delicious "
	"morsel.");
  set_id( ({ "cookie", "sugar cookie" }) );
  set_short("A soft sugar cookie");
  set_strength(3);
  set_long("Each one is baked with care and sprinkled with sugar.");
  set_weight(1);
  set_float_value(0.14);
  return;
}

