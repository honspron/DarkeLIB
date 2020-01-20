inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("enchanter object");
  set_id(({ "guildmaster object", "enchanter object", "symbol" }) );
  set_short("The symbol of the Enchanter Guildmaster");
  set_long(
"Type 'help guildmaster' for instructions.");
  set_join_room("/d/damned/guilds/join_rooms/enchanter_join");
  return;
}
