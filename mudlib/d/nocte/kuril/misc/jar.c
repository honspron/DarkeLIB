inherit "/std/bag_logic";

void create() {
  ::create();
  set_id("jar");
  set_name("jar");
  set_short("A small jar");
  set_long(
	"A small glass jar with a large cork top.");
  set_weight(5);
  set_value(5);
	set_max_internal_encumbrance(5);
	set_possible_to_close(1);
	toggle_closed();
  return;
}
