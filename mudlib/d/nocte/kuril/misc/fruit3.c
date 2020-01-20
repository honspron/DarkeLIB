inherit "/std/food";

void create() {
  ::create();
  set_name("red berries");
  set_my_mess("Juice from the berries drips all over as you each the entire "
	"bunch.");
  set_id( ({ "berries", "red berries" }) );
  set_short("A bunch of red berries");
  set_strength(3);
  set_long("A bunch of ripe red berries.");
  set_weight(1);
  set_float_value(1.2);
  return;
}

