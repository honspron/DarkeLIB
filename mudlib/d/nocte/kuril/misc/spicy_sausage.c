inherit "/std/food";

void create() {
  ::create();
  set_name("spicy sausages");
  set_my_mess("Yum!  The spicy sausage burns your tongues is tastes great!");
  set_id( ({ "sausage", "spicy sausages", "spicy sausage" }) );
  set_short("A spicy sausage");
  set_strength(25);
  set_long("This spicy sausage is made with Lupo's own secret spices and ingredients.");
  set_weight(2);
  set_float_value(2);
  return;
}
