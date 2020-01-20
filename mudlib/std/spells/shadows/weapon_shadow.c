//    A generic shadow for weapons.  It can do just about anything.
//    -Diewarzau
//    DarkeLIB 1.0 1/13/96

#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string expire_mesg;
mapping extra_wc;
mapping auto_crits;
int hit_bonus;
int extra_enchant;
int extra_crit;
string stack_key;

void set_stack_key(string str) {
  stack_key = str;
}

int query_stack(string key) {
  int res;
  
  res = (int)next_shadow()->query_stack(key);
  if(key != stack_key) return res;
  if(!res) res = 1;
  else res++;
  return res;
}

void set_enh_critical(int x) { extra_crit = x; }

void set_enchantment(int x) { extra_enchant = x; }

void set_hit_bonus(int x) { hit_bonus = x; }

void set_extra_wc(mapping wc) { extra_wc = wc; }

void add_wc(string type, int amt) {
  if(!extra_wc) extra_wc = ([]);
  if(!extra_wc[type]) extra_wc += ([ type : amt ]);
  else extra_wc[type] = amt + extra_wc[type];
  return;
}

void remove_wc(string type) { map_delete(extra_wc, type); }

void set_auto_crits(mapping ac) { auto_crits = ac; }

void add_auto_crit(string crit, int chance) {
  if(!auto_crits) auto_crits = ([]);
  if(!auto_crits[crit]) auto_crits += ([ crit : chance ]);
  else auto_crits[crit] = chance + auto_crits[crit];
  return;
}

void remove_auto_crit(string crit) { map_delete(auto_crits, crit); }

mapping query_all_wc() {
  mapping tmp;
  int i;
  string *wc_keys;

  tmp = (mapping)next_shadow()->query_all_wc();
  if(!tmp) tmp = ([]);
  if(!extra_wc) return tmp;
  i = sizeof(wc_keys = keys(extra_wc));
  while(i--) {
    if(tmp[wc_keys[i]]) tmp[wc_keys[i]] += extra_wc[wc_keys[i]];
    else tmp += ([ wc_keys[i] : extra_wc[wc_keys[i]] ]);
  }
  return tmp;
}

mixed query_enh_critical() {
  mixed ret;

  ret = next_shadow()->query_enh_critical();
  if(!ret) return extra_crit;
  if(intp(ret)) return ret + extra_crit;
  if(mapp(ret)) return map_mapping(ret, (: $2 + $3 :), extra_crit);
  return 0;
}

string *query_wc_types() {
  if(!mapp(extra_wc)) return (string *)next_shadow()->query_wc_types();
  return distinct_array(keys(extra_wc) + (string *)next_shadow()->query_wc_types());
}

int query_wc(string type) {
  int res;

  res = (int)next_shadow()->query_wc(type);
  if(extra_wc && extra_wc[type]) res += extra_wc[type];
  return res;
}

string *query_auto_critical() {
  string *ret, *ac_keys;
  int i;

  ret = (string *)next_shadow()->query_auto_critical();
  if(!ret) ret = ({});
  if(!mapp(auto_crits)) return ret;
  i = sizeof(ac_keys = keys(auto_crits));
  while(i--) {
    if(random(100) < auto_crits[ac_keys[i]])
      ret += ({ replace_string(ac_keys[i], "#", "") });
  }
  return ret;
}

int query_hit_bonus() {
  int res;

  res = (int)next_shadow()->query_hit_bonus();
  if(hit_bonus) res += hit_bonus;
  return res;
}

mixed query_property(string what) {
  if(what != "enchantment" || !extra_enchant)
    return next_shadow()->query_property(what);
  return extra_enchant + (int)next_shadow()->query_property("enchantment");
}

varargs void start_shadow(object what, int dur, string mesg) {
  seteuid(UID_SHADOW);
  begin_shadow(what);
  who_shadowed = what;
  seteuid(getuid());
   if(dur) delayed_call("expire_weap", dur, this_object());
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



