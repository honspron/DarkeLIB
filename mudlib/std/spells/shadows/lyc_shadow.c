//	A user shadow that can be cloned and used to temporarily 
//	modify a player stat(s).  Configured so it is cumulative with other
//	such shadows.
//	DarkeLIB 0.1
//	Diewarzau 7/18/95

#include <security.h>

inherit "/std/spells/shadows/shadow";

mapping stat_mods;
int mod;
object who_shadowed;

void create() {
	seteuid(getuid());
	stat_mods = ([]);
}


void set_mod(string stat, int mod) {
    if(!stringp(stat) || !intp(mod)) return;
    stat_mods[stat] = mod;
    return;
}

int start_shadow(object ob) {
    if(!objectp(ob)) return 0;
    if(mapp(ob->query_property("lycanthrope mods")))
      stat_mods = ob->query_property("lycanthrope mods");    
    seteuid(UID_SHADOW);
    begin_shadow(ob);
    seteuid(getuid());
    who_shadowed = ob;
    return 1;
}

int query_skill(string what) {
    if(what == "melee") return (int)next_shadow()->query_skill("melee") + 30;
    else if(what == "dodge") return (int)next_shadow()->query_skill("dodge") 
	+ 20;
    else return (int)next_shadow()->query_skill(what);
}

int query_stats(string str) {
    int mod;

    if(!stringp(str) || undefinedp(stat_mods[str])) mod = 0;
    else mod = stat_mods[str];
    return (int)next_shadow()->query_stats(str) + mod;
}

int query_lyc_status() { return 1; }

mixed query_property(string what) {
    if(what == "melee damage")
	return next_shadow()->query_property("l melee damage");
    else return next_shadow()->query_property(what);
}

string query_short() {
   if(!next_shadow()) return " ";
    if(!next_shadow()->query_short()) return " ";
    return (string)next_shadow()->query_short() + " ("+
	replace_string((string)who_shadowed->query_race(), "were", "")
	+ " form)";
}

