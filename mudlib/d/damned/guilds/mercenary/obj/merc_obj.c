//      Edited by Tailwind
//
//      Blessed ReturnLIB
//      Tailwind 10/28/98

inherit "/std/guilds/guildmaster_obj";

void create() {
  ::create();
  set_name("mercenary object");
  set_id(({ "guildmaster object", "mercenary object", "tattoo" }) );
  set_short("The Tattoo of the Mercenary Guildmaster");
  set_long(
"Type 'help guildmaster' for instructions.");
  set_join_room("/d/damned/guilds/join_rooms/mercenary_join");
  return;
}
