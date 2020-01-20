//    A move shadow which calls a function specified when the shadowed object moves,
//    Then nukes itself.
//
//    DarkeLIB 0.1
//    -Diewarzau 8/13/95

#include <move.h>
#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
function move_func;
mixed move_arg;

void set_move_func(function func) {
  if(!func || !functionp(func)) return;
  move_func = bind(func, this_object());
}

void set_move_arg(mixed arg) {
  move_arg = arg;
}

void start_shadow(object ob) {
  if(!ob || !objectp(ob)) return;
  who_shadowed = ob;
  seteuid(UID_SHADOW);
  begin_shadow(ob);
  seteuid(getuid());
  return;
}

int clean_up() {
  if(next_shadow()) return 1;
  else remove();
  return 0;
}

function query_m_func() { return move_func; }

mixed query_move_arg() { return move_arg; }

int move(object dest) {
  int res;

  if(!next_shadow()) return MOVE_NOT_ALLOWED;
  res = next_shadow()->move(dest);
  if(res != MOVE_OK) return res;
  if(move_func && functionp(move_func))
    catch((*move_func)(move_arg));
  remove();
  return res;
}
