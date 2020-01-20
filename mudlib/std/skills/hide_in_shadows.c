// Modified by Misery 030696 to fix typos

inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(11);
    set_fast_dev_cost(30);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill allows you to slip into the shadows of a room and remain "
"unnoticed until you move.  Note that players with high perception "
"skill will still see you.  Using the skill toggles it on and off.",
this_player());
}

void skill_func(object from, object at, string arg) {
  object ob, ob2;

  if(ob = (object)from->query("hide shad")) {
    message("my_action", "You emerge from the shadows.", from);
/* Used to be emergers from the shadows.
   Fixed - Misery 030696
 */
message("other_action", (string)from->query_cap_name()+
  " emerges from the shadows.",
  environment(from), ({ from }));
ob->external_destruct(ob);
from->set("hide shad", 0);
remove();
return;
}
message("my_action", "You quietly slip into the shadows.", 
  from);
seteuid(getuid());
ob = new("/std/spells/shadows/hide_shadow");
from->set("hide shad", ob);
ob->start_shadow(from);
ob2 = new("/std/spells/shadows/move_shadow");
ob2->set_move_func( (: call_other, ob, "external_destruct" :) );
ob2->set_move_arg(ob);
ob2->start_shadow(from);
remove();
return;
}

