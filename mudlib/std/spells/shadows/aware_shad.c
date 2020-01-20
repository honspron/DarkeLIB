#include <security.h>
inherit "/std/spells/shadows/shadow";

object who_shadowed;
int pow;
string message;

void create() {
        seteuid(getuid());
        return;
}

void set_power(int x) { pow = x; }

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

int query_awareness() {return 1;}
int query_skill(string what) {
  if(what == "perception")
    return 20 * pow + (int)next_shadow()->query_skill("perception");
  return (int)next_shadow()->query_skill(what);
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
