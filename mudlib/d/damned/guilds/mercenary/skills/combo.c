#include <clock.h>
 
inherit "/std/skills/skill.c";
 
void create() {
    ::create();
    set_stat("constitution");
    set_dev_cost(21);
    set_fast_dev_cost(50);
    set_property("no target", 1);
}
 
void info() {
message("help",
"This skill may be used to gain multiple attacks in a round.  When you 'use' it, you will "
"attack at an increased pace for a short time.  This skill may only be used once per half "
"hour (mud time, see 'help calendar').",
        this_player());
}
 
 
void skill_func(object from, object at, string arg) {
  object ob;
 
  if((time() - (int)from->query_last_use("combo")) < HOUR/4)
    {
    message("info", "You are too tired to use this skill again yet.",
from);
    remove();
    return;
  }
  from->set_last_use("combo");
  seteuid(geteuid(this_object()));
  ob = new("/std/spells/shadows/combo_shad");
  ob->start_shadow(from, props["skill level"]);
  message("info", "You begin to hit with combination moves!", from);
  message("info", from->query_cap_name() + " begins to hit with combinations moves!",
        environment(from), ({ from }));
  remove();
  return;
}
