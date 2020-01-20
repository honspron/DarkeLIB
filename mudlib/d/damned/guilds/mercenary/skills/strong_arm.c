// Possibly change so that it increases damage and not just crits.

#include <clock.h>
 
inherit "/std/skills/skill.c";
 
void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(31);
    set_fast_dev_cost(79);
    set_property("no target", 1);
}
 
void info() {
message("help",
"This skill raises the critical level of a critical hit which works well in
conjunction with combo.  Strong Arm can only be used once
per hour (mud time, see 'help calendar').",
        this_player());
}
 
void skill_func(object from, object at, string arg) {
 
  object ob;
 
  if((time() - (int)from->query_last_use("strong arm")) < HOUR/4)
    {
    message("info", "You are too tired to use this skill again yet.",
from);
    remove();
    return;
  }
  from->set_last_use("strong arm");
  seteuid(geteuid(this_object()));
  ob = new("/std/spells/shadows/strong_arm_shad");
  ob->start_shadow(from, props["skill level"]);
  message("info", "You begin to strong arm your opponents!", from);
  message("info", from->query_cap_name() + " begins to strong arm his opponents!",
        environment(from), ({ from }));
  remove();
  return;
}
