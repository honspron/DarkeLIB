inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("elementalist object");
  set_short("The symbol of the Elementalist Guildmaster");
  set_id(({ "guildmaster object", "elementalist object", "symbol" }) );
  set_long(
	"This symbol takes the form of a small bejeweled wand. "
	"Type 'help guildmaster' for help.");
  set_join_room("/d/damned/guilds/join_rooms/elementalist_join");
  return;
}

