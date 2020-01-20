//	armour shadow for protection spells
//	DarkeLIB 0.1
//	Diewarzau 4/6/94

#include <std.h>
#include <security.h>
inherit "/std/spells/shadows/shadow";

object who_shadowed;
mapping ac;
string mesg;
string *limbs;
string stack_key;

void remove_ac(object ob) {
    if(ob != this_object()) {
        next_shadow()->remove_ac(ob);
	return;
    }
    if(mesg && stringp(mesg))
      message("info",mesg,who_shadowed);
    remove();
}

void set_stack_key(string str) { stack_key = str; }

int query_stack(string key) {
  int res;
  
  if(key != stack_key || !stack_key) return (int)next_shadow()->query_stack(key);
  res = (int)next_shadow()->query_stack(key);
  if(res) res++;
  else res = 1;
  return res;
}

mapping query_all_ac() { return ac; }

void set_limbs(string *which) {
    if(!limbs) limbs = ({});
    limbs = distinct_array(limbs + which);
}

void set_expire_message(string message) { mesg = message; }

varargs void set_shad_ac(int amt, string type) {
    int i;

    if(!ac) ac = ([]);
    if(!type || !stringp(type)) {
	i = sizeof(DAMAGE_TYPES);
	while(i--)
	    ac[DAMAGE_TYPES[i]] = amt;
    }
    else if(member_array(type, DAMAGE_TYPES) >= 0)
	ac[type] = amt;
    else ac[DAMAGE_TYPES[0]] = amt;
    return;
}

void start_shadow(object ob, int duration) {
    if(!ob || !duration) return;
    seteuid(UID_SHADOW);
    shadow(ob,1);
    seteuid(getuid());
    who_shadowed = ob;
  delayed_call("remove_ac", duration, this_object());
    return;
}

string query_sheeit() { return "sheeeit"; }

int query_ac(string limb, string type) {
    int tmp;

    if(!limbs || !sizeof(limbs) || member_array(limb,limbs) > -1)
	tmp = ac[type];
    else tmp = 0;
    tmp += (int)next_shadow("query_ac")->query_ac(limb,type);
    return tmp;
}
