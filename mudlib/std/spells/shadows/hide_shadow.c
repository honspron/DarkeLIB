#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;

void start_shadow(object who) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  return;
}

int query_hiding() {
  int res;
  
  if(!who_shadowed || !environment(who_shadowed)) {
    remove();
    return 0;
  }
  res = (int)next_shadow()->query_hiding();
  return res + (int)who_shadowed->query_skill("hide in shadows");
}

string query_short() {
  if(!next_shadow()->query_short()) return 0;
  return (string)next_shadow()->query_short() +
    " is hiding in the shadows.";
}

void external_destruct(object ob) {
  if(ob != this_object()) {
    next_shadow()->external_destruct(ob);
    return;
  }
  if(who_shadowed) who_shadowed->set("hide shad", 0);
  remove();
  return;
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

