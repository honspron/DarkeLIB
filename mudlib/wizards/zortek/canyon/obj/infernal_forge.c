//    A forge.
#include <move.h>
#include <daemons.h>

inherit "/std/Object";
inherit "/std/locker_logic";

void create() {
  ::create();
  set_property("no save", 1);
  set_id( ({ "greater forge", "infernal forge", "forge" }) );
  set_name("forge");
  set_short("Infernal Forge");
  set_long(@TEXT
An emerald glow seems to issue from this unearthly forge.  Its heat is
derived from the foul fires of hell.  It stands upon a base of humanoid
skulls and its bellows are unmistakably from the tanned hides of the same.
TEXT
);
  set_weight(1300000000);
  set_value(100034);
  return;
}

int register_num() { return 2; }
string query_storage_key() { return "null"; }

int query_is_locker() { return 1; }
string query_my_file() { return "null"; }

int move(mixed dest) {
  object prev;
  int res;
  
  if(query_property("no get") && objectp(dest) && living(dest))
    return MOVE_NOT_ALLOWED;
  prev = environment();
  res = ::move(dest);
  if(res == MOVE_OK) {
    if(prev && prev->query_is_locker_room())
      SAVE_ITEMS_D->update_lockers(prev);
    if(environment() && environment()->query_is_locker_room())
      SAVE_ITEMS_D->update_lockers(environment());
  }
  return res;
}

