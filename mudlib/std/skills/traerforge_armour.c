#define ARMOUR ({\
"breast-plate", \
"corslet", \
"chain-coif", \
"scale-greaves", \
"scale-mail", \
"chain-greaves", \
"chain-mail", \
"great-helm", \
"tower-shield", \
"wall-shield", \
"large-shield", \
"small-shield", \
"buckler-shield", \
"gauntlet", \
"chain-glove", \
"metal-boots", \
"plate-bracer", \
"plate-greaves", \
"banded-mail", \
"metal-taces", \
"metal-visor" })

inherit "/std/skills/long_term.c";

string name, type;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(12);
    set_fast_dev_cost(35);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to forge metal armour.  In order to "
"forge armour, you need an armour blank.  This is "
"a long-term skill (see 'help long-term') and may take much real time to "
"finish.  If you are interrupted, you may pick up at a later time.  "
"\nType 'help "
"armour' for armour types available.\n"
"Usage: use forge armour at <blank> with <armour-name>\n"
"Example: use forge armour at blank 2 with breast-plate\n"
"NOTE: If you are picking up the skill after leaving off, you still need to "
"supply the weapon or armour type...this is to avoid accidentally starting over.",
	this_player());
}

int filter_armour(object item, string type) {
  if(!item->id("armour blank")) return 0;
  if(!item->query_property("progress "+name)) return 0;
  if((string)item->query_property("progress "+name) != type) return 0;
  return 1;
}

void skill_func(object from, object at, string arg) {
  object *inv, tmp;
  int time, qual;

  seteuid(getuid());
  arg = lower_case(arg);
  if(member_array(arg, ARMOUR) >= 0) {
    name = (string)from->query_name();
    inv = filter_array(all_inventory(from), "filter_armour",
      this_object(), arg);
    if(sizeof(inv)) at = inv[0];
    if(!at->id("armour blank")) {
      message("info", "You must use this skill on an armour blank.", from);
      remove();
      return;
    }
    if(!present("greater forge", environment(from))) {
      message("info", "You must be in a room with a greater forge to use this skill!",
          from);
      remove();
      return;
    }
    name = arg;
    type = "armour";
    tmp = new("/d/damned/virtual/"+arg+".armour");
      time = (700 + 3*(int)tmp->query_value()) / (props["skill level"]/16 + 1);
//     time = 1;
    tmp->remove();
    tmp = new("/wizards/diewarzau/obj/misc/ingot");
    tmp->set_material(replace_string((string)at->query_material(), "/", "", 1));
      time *= to_int(pow(to_float((int)tmp->query_value()/10), 0.4));
      time /= 2;
      if(time < 60) time = 60;
    if(wizardp(from)) time = 1;
    tmp->remove();
    at->set_property("progress "+name, arg);
    set_work_message("%^CYAN%^You pound on the armour blank.");
    start_work(at, from, time);
    return;
  }
  message("info", "See 'help armour' for the armour you can forge.",
      from);
  remove();
  return;
}

void finish_work(object from, object at) {
  object ob, ob2, ob3;
  float valf;
  int val, ac;

  seteuid(getuid());
  message("info", "%^CYAN%^You are finished forging!", from);
  ob2 = new("/std/Object");
  ob2->set_material("metal/iron");
  ob3 = new("/std/Object");
  ob3->set_material(replace_string((string)at->query_material(), "/", "", 1));
  ob = new("/d/damned/virtual/"+name+"."+type);
  ob->move(from);
  if(!present(ob,from)) {
  	message("info","%^CYAN%^You cannot carry your creation so it falls to the ground.",
  		from);
  	ob->move(environment(from));
  }
  if(ob->query_value()) {
    val = (int)ob->query_value();
    val = val * pow(to_float((int)ob3->prop("value") / (int)ob2->prop("value")), 0.5);
    ob->set_value(val);
   from->add_exp2(1000 + val/30);
  } else if(ob->query_float_value() && (float)ob->query_float_value() > 0.0) {
    valf = (float)ob->query_float_value();
    valf *= to_float((int)ob3->prop("value")) / to_float((int)ob2->prop("value"));
    ob->set_float_value(valf);
    from->add_exp2(974);
  }
  ob2->remove();
  ob3->remove();
  ob->set_material(replace_string((string)at->query_material(), "/", "", 1));
  ac = (int)ob->query_ac();
  ac = ac -1;
           ob->set_ac((ac * (props["skill level"]/15)) + random(20 - 35));
          if((int)ob->query_ac() < 39) ob->set_ac(39);
  if(intp(ob->prop("hardness")))
    ob->set_decay_rate((int)ob->prop("hardness"));
  at->remove();
  remove();
  return;
}

