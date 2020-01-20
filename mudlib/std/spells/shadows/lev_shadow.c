#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string e_message;

void create() {
	seteuid(getuid());
	return;
}

int start_shadow(object ob, int dur, string mesg) {
    if(!objectp(ob)) return 0;
    seteuid(UID_SHADOW);
    begin_shadow(ob);
    seteuid(getuid());
    who_shadowed = ob;
    e_message = mesg;
    call_out("expire_lev", dur, this_object());
    return 1;
}

int query_flying() { return 1; }

void expire_lev(object me) {
  if(me != this_object()) {
    next_shadow()->expire_lite(me);
    return;
  }
  message("info", e_message, who_shadowed);
  remove();
  return;
}


