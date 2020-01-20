#include <security.h>

inherit "/std/spells/shadows/shadow";

string exp_message;
object who_shadowed;
int max;

void set_max(int x) { max = x; }

int dark_vision() { return 1; }

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  exp_message = mesg;
  if(dur) call_out("expire_vision", dur, this_object());
  seteuid(getuid());
  return;
}

int query_sight_bonus() {
  int tlight, lite;
  int i;
  object *inv;

  tlight = total_light(who_shadowed);
  if((lite = tlight + (int)next_shadow()->query_sight_bonus()) < 2)
    return (2-tlight > max)?max:(2-tlight);
  else return (int)next_shadow()->query_sight_bonus();
}

void expire_vision(object me) {
  if(me != this_object()) {
    next_shadow()->expire_vision(me);
    return;
  }
  if(exp_message) message("info", exp_message, who_shadowed);
  remove();
  return;
}
