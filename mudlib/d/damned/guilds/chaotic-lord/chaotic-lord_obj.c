inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("chaotic-lord object");
  set_id(({ "guildmaster object", "chaotic lord object", "symbol" }) );
  set_short("The symbol of the Chaotic Lords Guildmaster");
  set_long("Type 'help guildmaster' for instructions.");
  set_join_room("/d/damned/guilds/join_rooms/chaotic-lord_join");
  return;
}
