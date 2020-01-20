#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
int resist, power;
string message;

void create() {
        seteuid(getuid());
        return;
}


int start_shadow(object ob, int dur, string msg) {
    if(!objectp(ob)) return 0;
    seteuid(UID_SHADOW);
    begin_shadow(ob);
    seteuid(getuid());
    who_shadowed = ob;
    message = msg;
    call_out("expire_me", dur, this_object());
    return 1;
}

int query_resist_num() {
  if(!next_shadow()->query_resist_num()) return 1;
  else return 1 + (int)next_shadow()->query_resist_num();
}

void set_resist(int x) { resist = x; }

mixed query_property(string what) {
    int ret;

    if(what == "magic resistance") {
      ret = resist;
      if(next_shadow()->query_property("magic resistance"))
        ret += (int)next_shadow()->query_property("magic resistance");
      return ret;
    }
    return next_shadow()->query_property(what);
}

void expire_me(object what) {
  if(what != this_object()) {
    next_shadow()->expire_me(what);
    return;
  }
  if(message)
    message("info", message, who_shadowed);
  remove();
}
