/*
 * A soul for guild master challenges
 *
 * Diewarzau 7/6/96
 * DarkeLIB 1.0
 */

#define ARENA "/wizards/diewarzau/rooms/gm_arena"

inherit "/std/Object";

void create() {
  ::create();
  set_name("challenge soul");
  set_id(({ "challenge soul" }));
  set_property("no save",1);
  return;
}

int drop() {
  return 1; 
}

void init() {
  add_action("pre_quit", "quit");
}

int pre_quit(string null) {
  if(!ARENA->query_cip() || this_player() !=
     (object)ARENA->query_gm()) return 0;
  ARENA->gm_quit();
  return 0;
}







