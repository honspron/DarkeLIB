inherit "/std/food";

void create() {
  ::create();
  set_name("tuna fish");
  set_my_mess("The tuna fish tastes great as you eat is whole.");
  set_id( ({ "fish", "tuna", "tuna fish" }) );
  set_short("A freshly caught tuna fish");
  set_strength(35);
  set_long("Fresh from the net of a local fisherman the tuna is a healthy "
	"addition to your diet.");
  set_weight(7);
  set_value(31);
}

