inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(15);
    set_fast_dev_cost(43);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill may be used to detect traps on chests, lock boxes, etc. "
"in order to avoid setting them off while picking the lock.  "
"Successfully using this skill also allows a bonus to disarming the "
"trap if you have the disarm trap skill.",
this_player());
}

void skill_func(object from, object at, string arg) {
  int roll;
  string desc;
  
  if(living(at)) {
    message("info", "Uh, I doubt that "+nominative(at)+
            " has a trap on "+objective(at)+".", from);
    remove();
    return;
  }
  if(!at->query_trap_level()) {
    message("info", "There appears to be no sign of a trap on "+
            lower_case((string)at->query_short())+".", from);
    message("info", (string)from->query_cap_name() +
            " inspects "+lower_case((string)at->query_short())+
            " for traps.", environment(from), ({ from }));
    remove();
    return;
  }
  message("info", (string)from->query_cap_name() +
          " inspects "+lower_case((string)at->query_short())+
          " for traps.", environment(from), ({ from }));
  if((random(100) + ((int)at->query_trap_level() - 6)*4) < props["skill level"]) {
    message("info", "%^MAGENTA%^%^BOLD%^You have located a trap!", from);
    switch((int)at->query_trap_level()) {
    case 1..4:
      desc = "poorly constucted";
      break;
    case 5..6:
      desc = "pretty cheap";
      break;
    default:
    case 7..10:
      desc = "fairly decent";
      break;
    case 11..15:
      desc = "well-constructed";
      break;
    case 16..19:
      desc = "very intimidating";
      break;
    case 20..10000:
      desc = "almost impossible to defeat";
      break;
    }
    if(props["skill level"] > 50 && desc)
      message("info", "The trap appears to be "+desc+".", from);
    if(props["skill level"] > 60)
      from->set("trap bonus", at);
    remove();
    return;
  }
  else if(random(100) < 10) {
    message("info", "%^RED%^%^BOLD%^OOPS!!!  You spring the trap!",
            from);
    message("info", "%^RED%^"+(string)from->query_cap_name() +
            " accidentally springs the trap!!!", environment(from),
            ({ from }) );
    at->spring_trap();
  }
  else
    message("info", "There appears to be no sign of a trap on "+
            lower_case((string)at->query_short())+".", from);
  remove();
  return;
}
