#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;

void create() {
	seteuid(getuid());
	return;
}

int start_shadow(object ob) {
    if(!objectp(ob)) return 0;
    seteuid(UID_SHADOW);
    begin_shadow(ob);
    seteuid(getuid());
    who_shadowed = ob;
    return 1;
}

int query_sight_bonus() { return -100; }

void revive() {
  next_shadow()->revive();
  remove();
  return;
}
