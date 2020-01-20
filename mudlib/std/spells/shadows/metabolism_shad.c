#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string exp_mesg;
int met_rate;
int count;

int query_metabolism() { return 1; }

void set_met_rate(int x) { met_rate = x; }

void create() {
  met_rate = 0;
  count = 0;
}

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  call_out("expire_met", dur, this_object());
  return;
}

void heart_beat() {
  int tmp, x;

  count++;
  message("info", "Beat.", who_shadowed);
  if(met_rate >= 0) {
    next_shadow()->heart_beat();
    tmp = met_rate;
  }
  else
    tmp = 100 + met_rate;
  if(tmp < 0) tmp = 0;
  if(tmp == 0) return;
  x = 100/tmp;
  if(x < 1) x = 1;
  if(count%x == 0)
    next_shadow()->heart_beat();
  if(tmp <= 100) return;
  x = 100/(tmp-100);
  if(count%x == 0)
    next_shadow()->heart_beat();
  if(tmp <= 200) return;
  x = 100/(tmp-200);
  if(count%x == 0)
    next_shadow()->heart_beat();
  return;
}

void expire_met(object me) {
  if(me != this_object()) {
    next_shadow()->expire_met(me);
    return;
  }
  message("info", exp_mesg, who_shadowed);
  remove();
  return;
}

