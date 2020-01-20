inherit "/std/food";

void create() {
  ::create();
  set_name("perch");
  set_my_mess("The perch tastes great as you eat is whole.");
  set_id( ({ "fish", "perch" }) );
  set_short("A freshly caught perch");
  set_strength(20);
  set_long("Fresh from the net of a local fisherman the perch is a healthy "+
	"addition to your diet.");
  set_weight(3);
  set_value(17);
}

