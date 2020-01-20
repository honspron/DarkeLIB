inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("thief object");
  set_short("The symbol of the Thief Guildmaster");
  set_id(({ "guildmaster object", "thief object", "symbol" }) );
  set_long(
"This symbol takes the form of a small bejeweled cross.  Type "
"'help guildmaster' for help.");
  set_join_room("/d/damned/guilds/join_rooms/thief_join");
  return;
}

