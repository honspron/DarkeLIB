inherit "/std/locker_room";

void create() {
  ::create();
  set_property("indoors",1);
  set_property("light",2);
  add_exit("/d/damned/guilds/seer/rooms/main_room", "down");
  add_exit("/d/damned/guilds/seer/rooms/trans_room","up");
  set("short","Treasury Vault of the Visionaries");
  set("long", @TEXT
You have entered the treasury vault of the Visionaries.  Within
these walls you may store your treasures and belongings safely
from those that would covet your belongings.  Due to the strict
communal code of honor, it is understood that the items left
here are expected to be used by any Seer that should have the
need.  The staircase continues upward to the top of the tower
and proceeds back down into the heart of the guild.
TEXT
);
}
void reset() {
  object mon;
  
  if(!present("falstaf", this_object())) {
    mon = new("/d/damned/guilds/seer/mobs/falstaf");
    mon->move(this_object());
  }
}
