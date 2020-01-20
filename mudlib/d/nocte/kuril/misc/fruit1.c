inherit "/std/food";

void create() {
  ::create();
  set_name("star fruit");
  set_my_mess("Yum, this star fruit is just delicious.");
  set_id( ({ "fruit", "star fruit" }) );
  set_short("A ripe star fruit");
  set_strength(6);
  set_long("Imported from some distant jungle, if you hold the fruit on end, "
	"and look from above, it looks just like a five pointed star.");
  set_weight(2);
  set_float_value(1);
  return;
}

