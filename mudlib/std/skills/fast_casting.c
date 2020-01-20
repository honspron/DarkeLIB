inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(16);
    set_fast_dev_cost(38);
    set_property("no target", 1);
}

void info() {
message("help",
"This skill is used in conjunction with spell casting.  If used with "
"the simple syntax 'use fast casting', the next spell's "
"casting time is halved.  "
"The skill level determines how often this skill may be used.  At 5%, it may only "
"be used once per half hour (real time), while at 100%, it may be used once every 3 minutes "
"(real time)."
	, this_player());
}

void skill_func(object from, object at, string arg) {
  object ob;
  
  if(props["skill level"] < 0) props["skill level"] = 0;
  if((time() - (int)from->query_last_use("fast casting")) < (3600 / (props["skill level"]/5+1)))
    {
    message("info", "You may only use this skill once every "+
      sprintf("%d minutes (real time).", (120 / (props["skill level"]/5+1))), from);
    remove();
    return;
  }
  from->set_last_use("fast casting");
  if(from->query("focus casting")) {
    from->set("focus casting", 0);
    if(ob=from->query("focus ob")) {
      if((string)ob->query_type() != "fast") {
        message("info", "You may only use one type of spell augmentation skill per spell.",
          from);
        remove();
        return;
      }
      else ob->remove();
    }
    message("info", "You are no fast casting.", from);
    remove();
    return;
  }
  else {
    from->set("focus casting", 1);
    message("info", "Your next spell will be fast-cast.", from);
    ob = new("/wizards/diewarzau/obj/misc/focus_ob");
    ob->move(from);
    ob->set_caster(from);
    ob->set_type("fast");
    from->set("focus ob", ob);
    remove();
    return;
  }
}

