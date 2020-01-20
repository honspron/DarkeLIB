inherit "/std/skills/skill";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(14);
    set_fast_dev_cost(35);
    set_property("target type", "any");
    set_property("must be present",1);
}
void info() {
message("help", "This skill is used to sense the strength of the magical aura on "
"weapons. The greater the aura, the greater the chance that a weapon will shatter if it "
"is enchanted or runed further. This skill will show an approximate level of the magical aura on the weapon. At 75% or higher, this will also show and approximate chance of breaking the weapon upon further enchantments or runes.",
this_player());
}


void skill_func(object from, object at, string arg) { 
  int old;
  string tmp;

  if(!at->is_weapon()) {
    message("info", "This skill must be used on a weapon.", from);
    return;
  }

  old = (int)at->prop("brittle");
  old += (random(30) - 15) / (props["skill level"]/10);
  if(old < 0) old = 0;
  tmp = "The weapon's aura is ";
  switch(old) {
  default:
  case 0..3:
    tmp += "undetectable";
    break;
  case 4..10:
    tmp += "very weak";
    break;
  case 11..19:
    tmp += "weak";
    break;
  case 20..25:
    tmp += "not very strong";
    break;
  case 26..35:
    tmp += "fairly strong";
    break;
  case 36..55:
    tmp += "very strong";
    break;
  case 56..200:
    tmp += "blazing";
    break;
  }
  tmp += "\n";
  if(props["skill level"] >= 75) {
    tmp += "Upon further enchantment or runeing, the weapon has ";
    switch(old) {
    default:
    case 0..29:
      tmp += "no chance";
      break;
    case 30..35:
      tmp += "a small chance";
      break;
    case 36..50:
      tmp += "a modest chance";
      break;
    case 51..75:
      tmp += "a good chance";
      break;
    case 76..200:
      tmp += "almost a 100% chance";
      break;
    }
    tmp += " of breaking.\n";
  }
  message("info", "%^YELLOW%^You discover the following about the weapon...\n%^RESET%^"+ tmp, from);
  remove();
  return;
}

