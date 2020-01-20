#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
int curse;
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

int query_curse_num() {
  if(!next_shadow()->query_curse_num()) return 1;
  else return 1 + (int)next_shadow()->query_curse_num();
}

void set_curse(int x) { curse = x; }

mixed query_property(string what) {
    int ret;

    if(what == "curse") {
      ret = curse;
      if(next_shadow()->query_property("curse"))
	ret += (int)next_shadow()->query_property("curse");
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

