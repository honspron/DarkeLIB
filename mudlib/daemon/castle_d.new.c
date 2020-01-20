//  Castle update daemon...extremely simple.
//  Diewarzau
#include "/adm/include/rooms.h"
#include "/adm/include/security.h"
#include "/adm/include/daemons.h"

int no_dest(object item) {
  if(item->query_is_locker()) {
    return 0;
  }
  return 1;
}

void update_room(object what) {
  int i;
  object *inv;
  string name;

  if(!what->is_castle()) return;
  inv = filter_array(all_inventory(what), "no_dest", this_object());
  i = sizeof(inv);
  while(i--) inv[i]->move(ROOM_VOID);
  SAVE_ITEMS_D->update_lockers(what);
  name = base_name(what);
  seteuid(getuid(this_object()));
  seteuid(UID_ROOT);
  destruct(what);
  seteuid(getuid());
  i = sizeof(inv);
  while(i--)
    inv[i]->move(name);
  if(what=find_object(name))
    SAVE_ITEMS_D->update_lockers(what);
  return;
}

