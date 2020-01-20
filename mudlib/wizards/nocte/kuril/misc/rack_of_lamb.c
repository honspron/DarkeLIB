inherit "/std/food";

void create() {
  ::create();
  set_name("rack of lamb");
  set_my_mess("Oh my!  You can hardly believe you finished such an enormous "
	"rack of lamb.");
  set_id( ({ "rack", "lamb", "rack of lamb" }) );
  set_short("A rack of lamb");
  set_strength(50);
  set_long("Fresh from the butcher shop and cooked just right.");
  set_weight(15);
  set_float_value(25);
  return;
}

