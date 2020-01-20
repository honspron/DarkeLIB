inherit "/std/guilds/guildmaster_obj";



void create() {

  ::create();

  set_name("seer object");

  set_short("The Icon of the Great Oracle");

  set_id(({ "guildmaster object", "seer object", "symbol", "icon" }) );

  set_long(@TEXT

This icon is in the form of a pendant hanging from a silver box

chain.  At the center of the pendant is a stunning tiger's eye

stone that is set in a bed of jet and white jade.  On the reverse

side is the inscription, "help guildmaster"

TEXT

);

  set_join_room("/d/damned/guilds/join_rooms/seer_join");

  return;

}

