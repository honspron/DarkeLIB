#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
int no_stack;
function receive_func;
string exp_mesg;

void set_receive_func(function func) { receive_func = func; }

void set_no_stack(int stat) { no_stack = stat; }

int query_sanctuary() { return no_stack; }

void create() {
  receive_func = 0;
  no_stack = 0;
}

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  call_out("expire_sanc", dur, this_object());
  return;
}

int receive_objects() {
  object prev;

  prev = previous_object();
  if(!prev) return next_shadow()->receive_objects();
  if(!receive_func || (*receive_func)(prev)) return 0;
  return next_shadow()->receive_objects();
}

void expire_sanc(object me) {
  if(me != this_object()) {
    next_shadow()->expire_sanc(me);
    return;
  }
  message("info", exp_mesg, who_shadowed);
  remove();
  return;
}

