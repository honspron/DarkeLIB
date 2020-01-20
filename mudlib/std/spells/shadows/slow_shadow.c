#include <security.h>
#include <move.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
object shadow_ob;
string exp_mesg;

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  exp_mesg = mesg;
  if(dur) call_out("expire_haste", dur, this_object());
  seteuid(getuid());
  return;
}

int query_slow() { return 1; }

void expire_haste(object me) {
  if(me != this_object()) {
    next_shadow()->expire_haste(me);
    return;
  }
  if(exp_mesg)
    message("info", exp_mesg, who_shadowed);
  if(shadow_ob) shadow_ob->remove();
  remove();
  return;
}

void set_slow_ob(object ob) { shadow_ob = ob; }

int move(mixed dest) {
  object ob;
  int res;

  res = (int)next_shadow()->move(dest);
  if(res != MOVE_OK) return res;
  if(stringp(dest)) ob = load_object(dest);
  else ob = dest;
  who_shadowed->set("exits", (string *)ob->query_exits());
  shadow_ob->reset_exits();
  return res;
}

