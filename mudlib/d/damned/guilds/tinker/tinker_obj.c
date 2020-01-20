inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("tinker object");
  set_short("The symbol of the Tinker Guildmaster");
  set_id(({ "guildmaster object", "tinker object", "symbol" }) );
  set_long(
"This symbol takes the form of a small bejeweled hammer.  Type "
"'help guildmaster' for help.");
  set_join_room("/d/damned/guilds/join_rooms/tinker_join");
  return;
}

