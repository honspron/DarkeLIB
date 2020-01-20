//  	A join room for fighters, well commented and intended fo use as
//	an example room of this type.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95
//
//      Edited by Tailwind for the Mercenary Guild
//
//      -Tailwind 7/8/99
//	NOTE:  Before coding any guild, Diewarzau must know the filename
//	of the join_room so he can set the file privs accordingly.

#include <std.h>
#include </d/damned/guilds/mercenary/merc.h>

inherit "/std/guilds/vault_join_room";

void create() {
  //  IMPORTANT:  The following MUST appear before ::create();
  set_class_name("mercenary");

  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
     set_related_guilds(({ "fighter" }));
  set("short", "The Mercenaries' Guild Joining Room");
  set("long", "This is the infamous Mercenaries guild, where scoundrels of all types train their fighting skills so they can be of use to their employers. The sign of the Mercenary, a pair of crossed daggers, hangs above the door to the north. \n");
  //  The "\n" is important at the end of the long desc.

  set_exits( ([ "west" : "/d/damned/akkad/ak_sd3"
	      "north" : ROOMS+"train_room" ]) );

  set("guildmaster", MON+"merc_gm");
  //  The guildmaster is automatically cloned if no pc guildmaster is
  //  found.

  set_guild_obj(OBJ+"merc_obj");
  //  This file points to the guildmaster object.

  //  The following lines set the properties for the guild.

  set_property("base hp regen", 10);
  set_property("base mp regen", 1);
  //  Base healing per tick.  Note that the default is 3 for both.
  //  Keep in mind that this increases with level.

  set_property("hp advance", 50);
  set_property("mp advance", 5);
  //  Base advance per level im max mp/hp.  Default is 10.

  set_property("guild mods",
	([ "strength" :  10, "dexterity" : 10 ]) );
  //  Stat mods received upon joining.

  //  The following line is necessary:
  this_object()->reset();
  return;
}
