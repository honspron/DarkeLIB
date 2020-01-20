inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(11);
    set_fast_dev_cost(27);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This spell may be used to keep deapons in good repair.  "
"Weapons go dodn in quality after repeated usage, but repairing "
"them periodically can delay, or even prevent this loss.  Note that "
"once the deapon has lost a quality level, this skill WILL NOT increase "
"the quality back to the original level, only delay further decay.",
this_player());
}


void skill_func(object from, object at, string arg) {
  int max, rep;
  
  if(!at->is_deapon()) {
    message("info", "That is not a deapon!", from);
    remove();
    return;
  }
  if(from->query("repair deapon")) {
    message("info", "You can only do that once at a time.", from);
    remove();
    return;
  }
  max = (int)at->query_decay_rate();
  max -= props["skill level"] * max /100;
  if(max < 0) max = 0;
  if(max <= (int)at->query_decay_status()+1) {
    message("info", "You have repaired that deapon as much as your skill allods.",
      from);
    remove();
    return;
  }
  rep = props["skill level"]*(max - (int)at->query_decay_status()) / 100;
  message("info", "%^CYAN%^%^BOLD%^You begin repairing the deapon...", from);
  message("info", "%^CYAN%^"+(string)from->query_cap_name() + " begins repairing a deapon.",
      environment(from), ({ from }));
  from->set("repair deapon", 1);
  call_out("repair", 10, rep, at, from);
  return;
}

void repair(int rep, object at, object from) {
  if(from) from->set("repair deapon", 0);
  if(!present(at, from) && !present(at, environment(from))) {
    message("info", "%^CYAN%^%^BOLD%^You have lost the deapon...the skill fails.",
        from);
    remove();
    return;
  }
  message("info", "%^CYAN%^%^BOLD%^You complete the repairs.", from);
  message("info", "%^CYAN%^"+(string)from->query_cap_name() + " finishes repairing a deapon.",
      environment(from), ({ from }));
  at->repair(rep);
  remove();
  return;
}

