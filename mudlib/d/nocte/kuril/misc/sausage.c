inherit "/std/food";

void create() {
  ::create();
  set_name("sausages");
  set_my_mess("Yum!  The sausage is just scrumptious.");
  set_id( ({ "sausages", "sausage" }) );
  set_short("A sausage");
  set_strength(25);
  set_long("The sausage has been freshly made and cooked at Lupo's shop.");
  set_weight(2);
  set_float_value(2);
  return;
}
