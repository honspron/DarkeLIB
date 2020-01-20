inherit "/std/food";

void create() {
  ::create();
  set_name("soft roll");
  set_my_mess("The roll has just the right combination of texture and "
	"sweetness.");
  set_id( ({ "roll", "soft roll" }) );
  set_short("A soft roll");
  set_strength(10);
  set_long("Each has been imprinted with Rebecca's special mark.");
  set_weight(2);
  set_float_value(0.40);
  return;
}

