#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
int stealth_skill;
int hide_skill;
string exp_mesg;

void set_my_skill(int x) { stealth_skill = x; }

void set_hide_skill(int x) { hide_skill = x; }

void create() {
  stealth_skill = 0;
  hide_skill = 0;
}

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  exp_mesg = mesg;
  if(dur) call_out("expire_me", dur, this_object());
  seteuid(getuid());
  return;
}

void expire_me(object me) {
  if(me != this_object()) {
    next_shadow()->expire_me(me);
    return;
  }
  if(exp_mesg) message("info", exp_mesg, who_shadowed);
  remove();
  return;
}

int query_mag_stealth() { return 1; }

int query_stealth() {
  int res;
  
  if(!who_shadowed) {
    remove();
    return 0;
  }
  res = (int)next_shadow()->query_stealth();
  return res + stealth_skill;
}

int query_hiding() {
  int res;
  
  if(!who_shadowed) {
    remove();
    return 0;
  }
  res = (int)next_shadow()->query_hiding();
  if(hide_skill) return res + hide_skill;
  return res;
}
