inherit "/std/locker_room";

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",3);
   add_exit("rg_skills", "northwest");
   set("short","The Forge Room");
   set("long", "This room is very hot because of the fires heating the
forge. This room is where ranger's may blacksmith there weapons and
armour.");
new("/d/damned/guilds/ranger/forge.c")->move(this_object());
}
