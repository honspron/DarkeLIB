inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("fighter object");
  set_id(({ "guildmaster object", "fighter object", "symbol" }) );
  set_short("The symbol of the Fighter Guildmaster");
  set_long(
"Type 'help guildmaster' for instructions.");
  set_join_room("/d/damned/guilds/join_rooms/fighter_join");
  return;
}
