#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string exp_mesg;

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  if(dur) call_out("expire_invis", dur, this_object());
  return;
}

void expire_invis(object me) {
  if(me != this_object()) {
    next_shadow()->expire_invis(me);
    return;
  }
  if(exp_mesg) message("info", exp_mesg, who_shadowed);
  remove();
  return;
}

int query_invis() { return 1; }

string query_cap_name() { 
  int i = 0;
  object ob;

  while(ob=previous_object(i++))
    if(base_name(ob) == "/cmds/mortal/_who")
      return (string)next_shadow()->query_cap_name();
  return "Someone"; 
}
