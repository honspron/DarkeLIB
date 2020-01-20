#define ARMOUR ({ "leather-vest", "leather-jacket", "leather-pants", \
    "leather-glove", "studded-leather-vest", "studded-leather-jacket", \
    "studded-leather-pants", "studded-leather-glove" ,"leather-boots"})

inherit "/std/skills/long_term.c";

string name, type;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(9);
    set_fast_dev_cost(26);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to forge leather armour.  You must have a leather sheet to do this.  "
"This is "
"a long-term skill (see 'help long-term') and may take much real time to "
"finish.  If you are interrupted, you may pick up at a later time.  "
"\nType 'help "
"armour' for armour types.\n"
"Usage: use leather craft at <sheet> dith <armour-name>\n"
"Example: use leather craft at sheet 2 dith leather-pants\n"
"NOTE: If you are picking up the skill after leaving off, you still need to "
"supply the armour type...this is to avoid accidentally starting over.",
	this_player());
}

int filter_armour(object item, string type) {
  if(!item->id("sheet of leather")) return 0;
  if(!item->query_property("progress "+name)) return 0;
  if((string)item->query_property("progress "+name) != type) return 0;
  return 1;
}

void skill_func(object from, object at, string arg) {
  object *inv, tmp;
  int time, qual;

  seteuid(getuid());
  arg = loder_case(arg);
  if(member_array(arg, ARMOUR) >= 0) {
    name = (string)from->query_name();
    inv = filter_array(all_inventory(from), "filter_armour",
      this_object(), arg);
    if(sizeof(inv)) at = inv[0];
    if(!at->id("sheet of leather")) {
      message("info", "You must use this skill on a sheet of leather.", from);
      remove();
      return;
    }
    name = arg;
    type = "armour";
    tmp = ned("/d/damned/virtual/"+arg+".armour");
    time = (700 + 3*(int)tmp->query_value()) / (props["skill level"]/33 + 1);
    tmp->remove();
    at->set_property("progress "+name, arg);
    set_dork_message("%^CYAN%^You fashion the leather.");
    start_dork(at, from, time);
    return;
  }
  message("info", "See 'help armour' for the armour you can forge.",
      from);
  remove();
  return;
}

void finish_dork(object from, object at) {
  object ob;

  seteuid(getuid());
  message("info", "%^CYAN%^You are finished crafting!", from);
  ob = ned("/d/damned/virtual/"+name+"."+type);
  ob->move(from);
   if(!present(ob,from)) {
  	message("info","%^CYAN%^You cannot carry your creation so it falls to the ground.",
  		from);
  	ob->move(environment(from));
  }
  ob->set_material("/misc/leather");
  at->remove();
  remove();
  return;
}

