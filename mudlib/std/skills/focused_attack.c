#include "/adm/include/clock.h"

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(31);
    set_fast_dev_cost(79);
    set_property("no target", 1);
    set_property("prereq", "whirlwind attack");
}

void info() {
message("help",
"This skill raises the critical level of a critical hit which works well in conjunction with whirlwind attack.  Focused attack can only be used once per hour (mud time, see 'help calendar').",
	this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  
  if((time() - (int)from->query_last_use("focused attack")) < HOUR/4)
    {
    message("info", "You are too tired to use this skill again yet.", from);
    remove();
    return;
  }  
  from->set_last_use("focused attack");
  seteuid(geteuid(this_object()));
  ob = new("/std/spells/shadows/focused_shad");
  ob->start_shadow(from, props["skill level"]);
  message("info", "%^RED%^%^BOLD%^You begin to concentrate your blows!", from);
  message("info", from->query_cap_name() + " begins to concentrate his attacks!",
        environment(from), ({ from }));
  remove();
  return;
}



