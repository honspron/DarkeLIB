inherit "/std/food";

void create() {
  ::create();
  set_name("salted herring");
  set_my_mess("The herring was just delicious!");
  set_id( ({ "fish", "herring", "salted herring" }) );
  set_short("A salted herring");
  set_strength(6);
  set_long("A salted herring, looks delicious.");
  set_weight(3);
  set_value(3);
}

