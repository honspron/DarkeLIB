//    A generic shadow for weapons.  It can do just about anything.
//    -Diewarzau
//    DarkeLIB 1.0 1/13/96

#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string expire_mesg;
int dice;
int sides;

void set_dice(int x) { dice = x; }
void set_sides(int x) { sides = x; }

int vampiric_func(object who) {
  int res, i, mult;
  object wield;

  res = 0;
  if(dice < 0) {
    mult = -1;
    dice *= -1;
  } else
    mult = 1;
  for(i=1; i<=dice; i++) res += 1+random(sides);
  res *= mult;
  who->add_hp(-1 * res);
  if(environment(who_shadowed) && living(wield=environment(who_shadowed)))
    wield->add_hp(res);
     message("info", "%^RED%^Vamp BLADE WORKS should add%^RESET%^"+res, wield);
  return 0;
}

int query_vampiric() { return 1; }

mixed query_hit() {
  mixed res;

  res = next_shadow()->query_hit();
  if(functionp(res))
    return ({ res, (: call_other, who_shadowed, "vampiric_func" :) });
  else if(pointerp(res))
    return res + ({ (: call_other, who_shadowed, "vampiric_func" :) });
  else
    return (: call_other, who_shadowed, "vampiric_func" :);
}

varargs void start_shadow(object what, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(what);
  who_shadowed = what;
  seteuid(getuid());
  if(dur) call_out("expire_weap", dur, this_object());
  if(mesg) expire_mesg = mesg;
  return;
}

void expire_weap(object me) {
  object who;
  
  if(me != this_object()) {
    next_shadow()->expire_weap(me);
    return;
  }
  if(objectp(who = who_shadowed->query_wielded()) && expire_mesg)
    message("info", expire_mesg, who);
  remove();
  return;
}



