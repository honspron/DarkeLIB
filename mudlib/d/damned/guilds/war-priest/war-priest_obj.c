inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("war-priest object");
  set_short("The symbol of the War-Priest Guildmaster");
  set_id(({ "guildmaster object", "war-priest object", "symbol" }) );
  set_long(
"This symbol takes the form of a small silver ankh.  Type "
"'help guildmaster' for help.");
  set_join_room("/d/damned/guilds/join_rooms/war-priest_join");
  return;
}

