#define DAMAGE_STR ({ "no", "slight", "little", "moderate", "considerable", "much", "severe", "grave" })
#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
object mission_ob;
string exp_mesg;
int f_flag;
int damage;
int exp_flag;

void set_fumble(int stat) { f_flag = stat; }

void set_mission_ob(object ob) { mission_ob = ob; }

int query_mission() { return 1; }

void create() {
  f_flag = 0;
  damage = 0;
  exp_flag = 0;
}

void start_shadow(object who, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  exp_mesg = mesg;
  if(dur > 120)
    call_out("warn_expire", dur - 120, this_object(), 120);
  else if(dur > 60)
    call_out("warn_expire", dur - 60, this_object(), 60);
  else call_out("warn_expire", dur - 30, this_object(), 30);
  call_out("expire_mission", dur, this_object());
  return;
}

void warn_expire(object me, int to_go) {
  int idx;

  if(me != this_object()) {
    next_shadow()->warn_expire(me, to_go);
    return;
  }
  if((int)who_shadowed->query_max_hp() <= 0) idx = 7;
  else
    idx = 7*damage / (int)who_shadowed->query_max_hp();
  if(idx < 0) idx = 0;
  else if(idx > 7) idx = 7;
  message("info", "%^YELLOW%^Way of the Ranger expires in "+
          sprintf("%d min., %d sec.  %sYou have taken %s damage.",
                  to_go/60, to_go%60, "", DAMAGE_STR[idx]), 
          who_shadowed);
  to_go -= 20;
  if(to_go > 1)
    call_out("warn_expire", 20, this_object(), to_go);
  return;
}
 

int do_damage(string limb, int amt) {
  int res;

  if(member_array(limb, (string *)who_shadowed->query_limbs()) < 0)
    return 0;
  res = (int)who_shadowed->query_max_dam(limb)*2 - (int)who_shadowed->query_dam(limb);
  if(amt > res) amt = res;
  damage += amt;
  return amt;
}

void heal(int x) {
  if(x >= 0) {
    next_shadow()->heal(x);
    return;
  }
  if((x*-1) > (int)who_shadowed->query_hp())
    x = -1 * ((int)who_shadowed->query_hp() - 1); 
  damage += x*-1;
  return;
}

void add_hp(int x) {
//  object prev;

  if(exp_flag || x >= 0) {
    next_shadow()->add_hp(x);
    return;
  }
  if((x*-1) > (int)who_shadowed->query_hp())
    x = -1 * ((int)who_shadowed->query_hp() - 1);
  damage += x*-1;
  return;
}

void expire_mission(object me) {
  if(me != this_object()) {
    next_shadow()->expire_mission(me);
    return;
  }
  message("info", exp_mesg, who_shadowed);
  if(objectp(mission_ob))
    mission_ob->remove();
  who_shadowed->add_hp(-1*damage * (f_flag?2:1));
  remove();
  return;
}
