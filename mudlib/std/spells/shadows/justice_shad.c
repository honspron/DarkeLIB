#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string exp_mesg;
int f_flag;

int infinite_loop(object what);

void set_fumble(int stat) { f_flag = stat; }

varargs int query_justice(object me) { 
  if(me && me != this_object()) return (int)next_shadow()->
	query_justice(me);
  return 1; 
}

void create() {
  f_flag = 0;
}

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  call_out("expire_just", dur, this_object());
  return;
}

int do_damage(string limb, int amt) {
  int res;
  object prev;

  res = (int)next_shadow()->do_damage(limb, amt);
  if (who_shadowed->query_hp() - amt < 0)
    res = who_shadowed->query_hp();
  if(next_shadow()->query_mission()) return 0;
  if(infinite_loop(previous_object())) return 0;
  if(f_flag) prev = next_shadow();
  else if(previous_object() && living(previous_object()))
    prev = previous_object();
  else if(previous_object() && objectp(previous_object()->
				       query_caster()))
    prev = previous_object()->query_caster();
  else if(who_shadowed->query_current_attacker())
    prev = (object)who_shadowed->query_current_attacker();
  else return res;
  prev->do_damage((string)prev->return_target_limb(), res);
  return res;
}

void heal(int x) {
  object prev;

  next_shadow()->heal(x);
  if(x >= 0)
    return;
  if(next_shadow()->query_mission()) return;
  if((x*-1) > (int)who_shadowed->query_hp())
    x = -1 * ((int)who_shadowed->query_hp() - 1);
  if(infinite_loop(previous_object())) return;
  if(f_flag) prev = next_shadow();
  else if(previous_object() && living(previous_object()))
    prev = previous_object();
  else if(previous_object() && objectp(previous_object()->
                                       query_caster()))
    prev = previous_object()->query_caster();
  else if(who_shadowed->query_current_attacker())
    prev = (object)who_shadowed->query_current_attacker();
  else return;
  prev->heal(x);
  return;
}

void add_hp(int x) {
  object prev;

  next_shadow()->add_hp(x);
  if(x >= 0)
    return;
  if(next_shadow()->query_mission()) return;
  if((x*-1) > (int)who_shadowed->query_hp())
    x = -1 * ((int)who_shadowed->query_hp() - 1);
  if(infinite_loop(previous_object())) return;
  if(f_flag) prev = next_shadow();
  else if(previous_object() && living(previous_object()))
    prev = previous_object();
  else if(previous_object() && objectp(previous_object()->
                                       query_caster()))
    prev = previous_object()->query_caster();
  else if(who_shadowed->query_current_attacker())
    prev = (object)who_shadowed->query_current_attacker();
  else return;
  prev->add_hp(x);
  return;
}

int infinite_loop(object what) {
  if(!what || !objectp(what)) return 0;
  if(what->query_justice(what)) return 1;
  return 0;
}

void expire_just(object me) {
  if(me != this_object()) {
    next_shadow()->expire_just(me);
    return;
  }
  message("info", exp_mesg, who_shadowed);
  remove();
  return;
}

