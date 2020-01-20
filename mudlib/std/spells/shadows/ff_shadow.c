#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string e_message;
int light;

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
    call_out("expire_lite", dur, this_object());
    return 1;
}

void set_light(int x) { light = x; }

mixed query_property(string what) {
  if(what != "light") return next_shadow()->query_property(what);
  return (int)next_shadow()->query_property("light") + light;
}

string query_short() {
  return (string)next_shadow()->query_short() +
    	" (faerie fire)";
}

void expire_lite(object me) {
  if(me != this_object()) {
    next_shadow()->expire_lite(me);
    return;
  }
  message("info", e_message, who_shadowed);
  remove();
  return;
}


