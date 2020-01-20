#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string exp_mesg;
int penalty;

void set_penalty(int x) { penalty = x; }

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  if(dur) call_out("expire_blur", dur, this_object());
  return;
}

void expire_blur(object me) {
  if(me != this_object()) {
    next_shadow()->expire_blur(me);
    return;
  }
  if(exp_mesg) message("info", exp_mesg, who_shadowed);
  remove();
  return;
}

int sight_adjustment(object who) {
  int res;

  res = (int)next_shadow()->sight_adjustment();
  res += penalty;
  return res;
}

int query_blurred() { return 1; }


