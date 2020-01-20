#include "/adm/include/security.h"
#define NO_CAP_NAME ({ "/cmds/mortal/_say", \
  "/cmds/mortal/_tell", "/cmds/mortal/_yell", \
  "/cmds/mortal/_reply" })
#define REVEAL ({ "/cmds/mortal/_tell", \
  "/cmds/mortal/_reply", "/cmds/mortal/_shout", "/daemon/chat" })

inherit "/std/spells/shadows/shadow";

object who_shadowed;
string shadowed_str;
string new_short;
int skill;
string new_cap_name;

void set_new_short(string news) { new_short = news; }

void set_new_cap_name(string news) { new_cap_name = news; }

void set_my_skill(int x) { 
  shadowed_str = file_name(this_object());
  skill = x; 
}

void start_shadow(object who) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  return;
}

string query_short() {
  object prev;

  if(!next_shadow()->query_short()) return 0;
  if(objectp(this_player())) prev = this_player();
  else if(previous_object() && living(previous_object()))
    prev = previous_object();
  else
    prev = 0;
  if(!prev) return (string)next_shadow()->query_short();
  if(prev->query("fooled:"+shadowed_str))
    return new_short;
  else if(skill_contest((int)prev->query_skill("perception"),
			skill) != 1) {
    previous_object()->set("fooled:"+shadowed_str, 1);
    return new_short;
  }
  else return (string)next_shadow()->query_short();
}

string query_cap_name() {
  object prev, *inv;
  int i;

  if(!next_shadow()->query_short()) return "Someone";
  if(previous_object() &&
    member_array(base_name(previous_object()), REVEAL) >= 0 &&
    new_cap_name != (string)next_shadow()->query_cap_name()) {
    return (string)next_shadow()->query_cap_name();
  }
  if(previous_object() &&
    member_array(base_name(previous_object()), NO_CAP_NAME) >= 0 &&
    new_cap_name != (string)next_shadow()->query_cap_name()) {
    inv = all_inventory(environment(who_shadowed));
    i = sizeof(inv);
    while(i--) {
      if(!inv[i]->is_pet()) continue;
      if(lower_case(new_cap_name) == (string)inv[i]->query_owner())
        return (string)next_shadow()->query_cap_name();
    }
  }
  if(objectp(this_player())) prev = this_player();
  else if(previous_object() && living(previous_object()))
    prev = previous_object();
  else
    prev = 0;
  if(!prev) return new_cap_name;
  if(prev->query("fooled:"+shadowed_str))
    return new_cap_name;
  else if(skill_contest((int)prev->query_skill("perception"),
                        skill) != 1) {
    previous_object()->set("fooled:"+shadowed_str, 1);
    return new_cap_name;
  }
  else return (string)next_shadow()->query_cap_name();
}

void external_destruct(object ob) {
  if(ob != this_object()) return;
  if(who_shadowed)
    who_shadowed->set("diguise shad", 0);
  ::external_destruct(ob);
  return;
}

