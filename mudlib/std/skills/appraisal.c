inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(18);
    set_fast_dev_cost(44);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to appraise the value of items. A higher skill "
"will give a more accurate appraisal. ",
this_player());
}


void skill_func(object from, object at, string arg) {
  int roll, accuracy, val;
  
  if(at->is_living()) {
    message("info", "You cannot appraise a living thing!", from);
    remove();
    return;
  }
  roll = props["skill level"]/2 + random(props["skill level"]/2);

  switch (roll) {
  case 00..20:
    accuracy = 500;
    break;
  case 21..40:
    accuracy = 100;
    break;
  case 41..60:
    accuracy = 50;
    break;
  case 61..80:
    accuracy = 10;
    break;
  case 81..10000:
    accuracy = 1;
  default:
  }

  val = at->query_value();
  val /= accuracy;
  val *= accuracy;

  if (accuracy == 500) {
    message("info", "This item is absolutely priceless!", from);
    remove();
    return;
  }

  if (val == 0) {
    message("info", "You are unsure of this item's value", from);
    remove();
    return;
  }
  message("info", "You think the item is worth approximately "+val+
	  " silver.", from);
  remove();
  return;
  
}

