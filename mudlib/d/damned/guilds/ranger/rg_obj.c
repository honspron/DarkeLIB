inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("ranger object");
  set_short("The symbol of the Ranger Guildmaster");
  set_id(({ "guildmaster object", "ranger object", "symbol" }) );
  set_long(
"This symbol takes the form of a small bejeweled sword.  Type "
"'help guildmaster' for help.");
  set_join_room("/d/damned/guilds/join_rooms/ranger_join");
  return;
}
