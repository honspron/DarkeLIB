inherit "/std/locker_room";

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
add_exit("rg_skills", "west");
   set("short","The Tinker Treasury");
set("long", "This room is more or less a cuby hole.\n"
"This is the Ranger Treasury. Any ranger with proper permissions mey store
items here. Beware any item left in the lockers is open for use by the
whole guild. MAKE SURE you close all chests and lockers after using them,
if not all items inside are gone for good."
);
}
