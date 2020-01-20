inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(15);
    set_fast_dev_cost(38);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill allows you to heighten your awareness of your surroundings.  "
"Despite the name, this skill has little use in combat, but it is useful to "
"spot covert activities, such as theft or back stabbing.  While this skill is "
"on, you will move slowly, i.e., there will be a delay everytime you move "
"a step.  The higher the skill level, the greater the bonus to your "
"awareness.\n"
"Usage: 'use combat awareness' to toggle on and off."
	, this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  object ob2;
  
  if(from->query("c awareness")) {
    message("info", "You cease moving cautiously.",
            from);
    if(ob=from->query("c aware shad"))
      ob->external_destruct(ob);
    if(ob=from->query("c aware ob"))
      ob->remove();
    if(ob=from->query("c aware sk shad"))
      ob->external_destruct(ob);
    from->set("c awareness", 0);
    return;
  } else {
    ob=new("/wizards/diewarzau/obj/misc/slow_ob");
    from->set("exits", (string *)environment(from)->query_exits());
    ob->move(from);
    ob2 = new("/std/spells/shadows/slow_shadow");
    ob2->set_slow_ob(ob);
    ob2->start_shadow(from, 0, "");
    from->set("c aware shad", ob2);
    from->set("c aware ob", ob);
    ob = new("/std/spells/shadows/skill_shadow");
    ob->add_new_skill_bonus("perception", 16+props["skill level"]/2);
    ob->add_new_skill_bonus("reverse stroke", 21+props["skill level"]/3);
    ob->start_shadow(from, 0, "");
    from->set("c aware sk shad", ob);
    message("info", "You begin to move with caution.", from);
    from->set("c awareness", 1);
    return;
  }
}
