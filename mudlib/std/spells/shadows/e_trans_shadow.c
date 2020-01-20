#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;
int melee;
int mskill;
string *elements;
string message;

void create() {
	seteuid(getuid());
	return;
}

void set_melee(int x) { melee = x; }

void set_elements(string *ele) { elements = ele; }

void set_melee_skill(int x) { mskill = x; }

int start_shadow(object ob, int dur, string msg) {
    if(!objectp(ob)) return 0;
    seteuid(UID_SHADOW);
    begin_shadow(ob);
    seteuid(getuid());
    who_shadowed = ob;
    message = msg;
    delayed_call("expire_me", dur, this_object());
    return 1;
}

int query_d_trans() { return 1; }

mixed query_property(string what) {
  mapping tmp, tmp2;
  int i;
  string *mkeys;

  if(what == "melee damage") {
    tmp = allocate_mapping(30);
    i = sizeof(elements);
    while(i--) tmp[elements[i]] = melee;
    tmp2 = (mapping)next_shadow()->query_property("melee damage");
    if(!tmp2 || !mapp(tmp2)) return tmp;
    mkeys = keys(tmp2);
    i = sizeof(mkeys);
    while(i--) {
      if(tmp[mkeys[i]]) tmp[mkeys[i]] += tmp2[mkeys[i]];
      else tmp[mkeys[i]] = tmp2[mkeys[i]];
    }
    return tmp;
  }
  return next_shadow()->query_property(what);
}

int query_skill(string what) {
  if(what == "melee")
    return mskill + (int)next_shadow()->query_skill("melee");
  return (int)next_shadow()->query_skill(what);
}

void expire_me(object what) {
  if(what != this_object()) {
    next_shadow()->expire_me(what);
    return;
  }
  if(message)
    message("info", message, who_shadowed);
  remove();
}
