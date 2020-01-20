#include <security.h>

inherit "/std/spells/shadows/shadow";

object who_shadowed;

void start_shadow(object who, int skill) {
  seteuid(UID_SHADOW);
  begin_shadow(who);
  who_shadowed = who;
  seteuid(getuid());
  call_out("end_skill", (5 + skill / 5 + random(skill / 3))*2, this_object());
  return;
}

void end_skill(object me) {
  if(me != this_object()) {
    next_shadow()->end_skill(me);
    return;
  }
  message("info", "%^CYAN%^You are tired of focusing your attacks....you stop.",
        who_shadowed);
  remove(this_object());
  return;
}

int query_focused_attack() {
   int foc_att;
     if((int)this_object()->query_skill("focused attack") > 100){
             foc_att = random(2)+1;
      }  else
             foc_att = 1;
   return;
}





