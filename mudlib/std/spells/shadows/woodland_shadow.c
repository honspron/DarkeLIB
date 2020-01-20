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

int query_woodland_stealth() { return 1; }

int query_stealth() {
  if(!who_shadowed || !environment(who_shadowed)) {
    remove();
    return 0;
  }
  if(capitalize((string)environment(who_shadowed)->query_terrain()) == "F" ||
     capitalize((string)environment(who_shadowed)->query_terrain()) == "J")
    return (int)who_shadowed->query_skill("woodland stealth");
  return 0;
}

int query_hiding() {
  if(!who_shadowed || !environment(who_shadowed)) {
    remove();
    return 0;
  }
  if(!environment(who_shadowed)->query_terrain()) return 0;
  if(capitalize((string)environment(who_shadowed)->query_terrain()) == "F" ||
     capitalize((string)environment(who_shadowed)->query_terrain()) == "J")
    return (int)who_shadowed->query_skill("woodland stealth");
  return 0;
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
