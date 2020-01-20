#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string stealth_skill;
string hide_skill;

void set_my_skill(string str) { stealth_skill = str; }

void set_hide_skill(string str) { hide_skill = str; }

void create() {
  stealth_skill = 0;
  hide_skill = 0;
}

void start_shadow(object who) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  return;
}

int query_stealth() {
  int res;
  
  if(!who_shadowed) {
    remove();
    return 0;
  }
  res = (int)next_shadow()->query_stealth();
  if(stealth_skill) return res + (int)who_shadowed->query_skill(stealth_skill);
  return res + (int)who_shadowed->query_skill("stealth");
}

string query_my_skill() {
  if(!stealth_skill) return "stealth";
  return stealth_skill;
}

int query_hiding() {
  int res;
  
  if(!who_shadowed) {
    remove();
    return 0;
  }
  res = (int)next_shadow()->query_hiding();
  if(hide_skill) return res + (int)who_shadowed->query_skill(hide_skill);
  return res;
}

void kill_ob(object who, int flag) {
  if(objectp(who) && who != who_shadowed) {
    next_shadow()->kill_ob(who, flag);
    remove();
  }
  else
    next_shadow()->kill_ob(who, flag);
  return;
}

