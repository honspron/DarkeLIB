inherit "/std/bag_logic";

void create() {
  ::create();
  set_id("flask");
  set_name("flask");
  set_short("A flask");
  set_long(
	"A glass flask for holding things.");
  set_weight(10);
  set_value(15);
	set_max_internal_encumbrance(15);
  return;
}
