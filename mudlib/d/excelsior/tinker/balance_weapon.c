#define FORGE_MATERIALS ({ "steel", "iron", "default" })

inherit "/std/skills/long_term.c";

string name;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(12);
    set_fast_dev_cost(32);
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill can be used to balance a weapon for use by the skill user- "
"a balanced weapon is more powerful then an unbalanced weapon in the hands "
"of the person it is balanced for, and less useful in the hands of everyone "
"else. This is a long-term skill and can take very much real time to complete. "
"(see 'help long-term') If you are interupted, you may pick up your work at a "
"later time.\n"
"usage: use balance weapon at <weapon>"
"\nexample: use balance weapon at long-sword"
"NOTE: If you are picking up the skill after leaving off, you still need to "
"supply the weapon name...this is to avoid accidentally starting over.\n"
"WARNING: balancing a weapon does carry with it the risk of ruining the "
"weapon. If you try to balance a weapon already balanced by you or anyone "
"else, the failure rate is higher then normal.",
	this_player());
}

int filter_weapon(object item) {
  if(!item->is_weapon()) return 0;
  if(!item->query_property("progress "+name)) return 0;
  return 1;
}

void skill_func(object from, object at) {
  int time, mod;
  seteuid(getuid());
  name = (string)from->query_name();
  if(!at->is_weapon()) {
    message("info", "You must use this skill on a weapon.", from);
    remove();
    return;
  }
  if(!present("greater forge", environment(from)) && member_array(
  		(string)at->query_property("material_name"),FORGE_MATERIALS) < 0) {
    message("info", "You must be in a room with a greater forge to use this skill "+
    	"on weapons of such materials!",from);
    remove();
    return;
  }
  else {
  	if(!present("forge", environment(from)) && member_array(
  		(string)at->query_property("material_name"),FORGE_MATERIALS) >= 0) {
  		message("info", "You must be in a room with a forge to use this skill.",
  			from);
    	remove();
    	return;
    }
  }
  if(at->query_wield()) {
  	message("info","You must unwield that weapon to work on it.",from);
  	remove();
  	return;
  }
  mod = props["skill level"];
  if(!mod) mod = 1;
  time = (2000 + (int)at->prop("hardness")) / mod;
  at->set_property("progress "+name, 1);
  set_work_message("%^CYAN%^You pound on the weapon.");
  start_work(at, from, time);
  return;
}

void finish_work(object from, object at) {
  int val,hit_bonus,wc_bonus,i;
  seteuid(getuid());
  if(at->query_property("balanced")) { i = 100000; }
  else { i = 2; }
  if(random(100) > props["skill level"]*random(20) && random(i)) {
  	message("info","%^RED%^DOH! You miss calculated your work! The "+
  		"weapon has become all but useless!",from);
  	at->set_decay_rate(0);
  	at->set_value(0);
  	remove();
  	return;
  }
  message("info", "%^CYAN%^You are finished balancing the weapon!", from);
  if(at->query_wielded()) at->__ActuallyUnwield();
  hit_bonus = (props["skill level"]*7)/(int)at->query_weight();
  wc_bonus = (props["skill level"]/8) + random(4);
  if(props["skill level"] < 10) wc_bonus = 0;
  val = (int)at->query_value();
  at->set_value(val - 2*wc_bonus - hit_bonus);
  if((int)at->query_value() <= 0) at->set_value(1);
  val = (int)at->query_decay_rate();
  at->set_decay_rate(val - 2*wc_bonus - hit_bonus - random(20) + 
  	(props["skill level"]/(random(20)+5)));
  if((int)at->query_decay_rate() <= 0) at->set_decay_rate(1);
  at->set_property("balanced",name);
  at->set_property("balanced hit bonus",hit_bonus);
  at->set_property("balanced wc bonus",wc_bonus);
  remove();
  return;
}

