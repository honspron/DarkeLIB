//	DarkeLIB 0.1
//	-Diewarzau 8/8/95

inherit "/std/guilds/skill_room";

void create() {
  object ob;
  ::create();
  set("short", "The Newbie Training Room");
  set("long", "This is the newbie train room which is temp till "+
   "a newbie joins a guild");
  set_property("light", 2);
  set_property("indoors", 1);
  set_property("no attack", 1);
  set_property("no magic", 1);
  set_property("no scry", 1);
  set_join_room("/d/damned/guilds/join_rooms/child_join");
  add_exit("/d/damned/guilds/join_rooms/child_join", "down");
  add_skill("consider", 1);
  add_skill("trade lore", 1, 1);
  add_skill("attack", 1);
  add_skill("melee", 1);
  add_skill("prospecting", 1, 1);
  add_skill("knife", 1);
  add_skill("blade", 1);
  add_skill("perception", 1);
  add_skill("swimming", 1);
  return;
}
