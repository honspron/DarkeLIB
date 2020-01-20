//  	A join room for fighters, well commented and intended fo use as
//	an example room of this type.
//
//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

//	NOTE:  Before coding any guild, Diewarzau must know the filename
//	of the join_room so he can set the file privs accordingly.


// tinker guild improved by Excelsior 
// 4/5/96
inherit "/std/guilds/join_room";

void create() {
  //  IMPORTANT:  The following MUST appear before ::create();
  set_class_name("tinker");

  ::create();
  set_property("light", 2);
  set_property("indoors", 1);
new("d/damned/guilds/join_rooms/tcan")->move(this_object());
  set_related_guilds(({ "fighter", "enchanter" }));
  set("short", "The Tinker's Guild Joining Room");
  set("long", 
	"You have found your way into a quaint little cottage. "+
	"There is an iron spiral staircase leading up from here. All "+
	"about the room are strange and wonderful things crafted by the "+
		"greatest tinkers of all time. You feel a great heat coming from a back room to the west, "+
		"and feel it may not be so quaint in that direction.\n");
	set_items((["staircase":"It is crafted out of "+
			"iron and looks very proffesionally done.",
		"things":"There is a sign nearby that says 'Look with your eyes not your hands.' Shucks."]));
  //  The "\n" is important at the end of the long desc.

  set_exits( ([ 
	      "east" : "/d/damned/akkad/ak_sd4",
	      "up" : "/d/damned/guilds/tinker/train_room",
	      "west" : "d/damned/guilds/tinker/tinker_shop" ]) );

//Class Check added by Maxwell 7/96
  set_pre_exit_functions(({"west" }), ({"class_check"}) );
//

  set("guildmaster", "/d/damned/guilds/tinker/tinker_gm");
  //  The guildmaster is automatically cloned if no pc guildmaster is
  //  found.

  set_guild_obj("/d/damned/guilds/tinker/tinker_obj");
  //  This is the filename for the guild's guildmaster object, carried
  //  by the PC guildmaster if any.

  //  The following lines set the properties for the guild.

  set_property("base hp regen", 7);
  set_property("base mp regen", 2);
  //  Base heling per tick.  Note that the default is 3 for both.
  //  Keep in mind that this increases with level.

  set_property("hp advance", 40);
  set_property("mp advance", 8);
  //  Base advance per level im max mp/hp.  Default is 10.

  set_property("guild mods",
	([ "strength" :  15, "constitution" : 5 ]) );
  //  Stat mods received upon joining.

  //  The following line is necessary:
  this_object()->reset();
  return;
}
int class_check(){
   if(this_player()->query_class() != "tinker" && !wizardp(this_player())){
     write("A magical force stops you from going in that direction.");
     return 0;
   }
   else
     return 1;
}
