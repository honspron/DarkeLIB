inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("necromancer object");
  set_id(({ "guildmaster object", "necromancer object", "symbol" }) );
  set_short("The symbol of the Necromancer Guildmaster");
  set_long(
"Type 'help guildmaster' for instructions.");
  set_join_room("/d/damned/guilds/join_rooms/necromancer_join");
  return;
}
