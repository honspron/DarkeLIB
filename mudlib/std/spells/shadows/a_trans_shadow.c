#define REAL_CAP ({ "/cmds/mortal/_tell", "/cmds/mortal/_reply" })
#define REAL_SHORT ({ "/cmds/mortal/_who" })
#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string e_message;
mapping new_melee;
mapping stat_mods;
string new_short;
string new_cap_name;

void create() {
	seteuid(getuid());
	return;
}

void set_new_short(string str) { new_short = str; }

void set_new_melee(mapping m) { new_melee = m; }

void set_atrans_mods(mapping m) { stat_mods = m; }

void set_new_cap(string str) { new_cap_name = str; }

string query_cap_name() {
  int i = 0;
  object ob;

  while(ob=previous_object(i++))
    if(member_array(base_name(ob), REAL_CAP) >= 0)
      return (string)next_shadow()->query_cap_name();
  return new_cap_name; 
}

int start_shadow(object ob, int dur, string mesg) {
    if(!objectp(ob)) return 0;
    seteuid(UID_SHADOW);
    begin_shadow(ob);
    seteuid(getuid());
    who_shadowed = ob;
    e_message = mesg;
    call_out("expire_lev", dur, this_object());
    return 1;
}

mixed query_property(string str) {
  if(str != "melee damage") return next_shadow()->query_property(str);
  return new_melee;
}

void set(string str, mixed val) {
  next_shadow()->set(str, val);
  if(str != "lyc ob" || !val) 
    return;
  message("info", "%^CYAN%^Animal transformation wears off.",
    who_shadowed);
  remove();
  return;
}

int query_stats(string str) {
  if(!stat_mods || !stat_mods[str]) return (int)next_shadow()->query_stats(str);
  return stat_mods[str] + (int)next_shadow()->query_stats(str);
}

string query_short() {
  int i = 0;
  object ob;

  while(ob=previous_object(i++))
    if(member_array(base_name(ob), REAL_SHORT) >= 0)
      return (string)next_shadow()->query_short();
  return new_short;
}

void expire_lev(object me) {
  if(me != this_object()) {
    next_shadow()->expire_lev(me);
    return;
  }
  message("info", e_message, who_shadowed);
  remove();
  return;
}


