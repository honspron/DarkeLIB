//    A shadow for elemental lore skills.
//
//    DarkeLIB 0.1
//    -Diewarzau 10/24/95

#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string element;

void set_element(string str) { element = str; }

void start_shadow(object who) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  return;
}

int query_skill(string str) {
  int tmp, ret;
  float val;

  if(str != "elementalism") return next_shadow()->query_skill(str);
  ret = next_shadow()->query_skill("elementalism");
  if(!ret) return 0;
  tmp = next_shadow()->query_skill(element + " lore");
  if(!tmp) return 0;
  return to_int(to_float(tmp+ret) / 2.05);
}

string query_element() { return element; }

