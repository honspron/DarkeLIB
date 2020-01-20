#define METAL ({\
"bastard-sword", \
"broad-sword", \
"dagger", \
"footman's-mace", \
"knife", \
"long-sword", \
"rapier", \
"scimitar", \
"short-sword", \
"spiked-gauntlet", \
"stiletto", \
"two-handed-sword" })

#define BOTH ({ \
"battle-axe", \
"footman's-flail", \
"glaive", \
"great-axe", \
"halberd", \
"hammer", \
"hand-axe", \
"military-fork", \
"military-pick", \
"morning-star", \
"shod-staff", \
"spear", \
"trident", \
"war-hammer" })

inherit "/std/skills/long_term";

string name, type,what;
object board;

void create() {
    ::create();
    set_stat("dexterity");
    set_dev_cost(12);
    set_fast_dev_cost(35);
    set_property("prereq", "blacksmith");
    set_property("target type", "any");
    set_property("must be present", 1);
}

void info() {
message("help",
"This skill is used to forge metal weapons out of any metal, even magical metals.  In order to forge weapons, "
"you need a weapon blank.  Some weapons have wooden components, and "
"require both carpentry skill and a wooden board to fashion.  This is "
"a long-term skill (see 'help long-term') and may take much real time to "
"finish.  If you are interrupted, you may pick up at a later time.  "
"\nType 'help weapons' to see what weapons can be forged.\n"
"Usage: use forge weapon at <blank> with <weapon-name>\n"
"Example: use forge weapon at blank 2 with long-sword\n"
"NOTE: If you are picking up the skill after leaving off, you still need to "
"supply the weapon type...this is to avoid accidentally starting over.",
	this_player());
}

int filter_board(object ob) {
	if(!ob->id("board")) return 0;
	if(ob->query_wood() <= 0) return 0;
	return 1;
}

object find_greatest_board(object where) {
	object *inv2, big;
	int n,i;
	inv2 = filter_array(all_inventory(where),"filter_board",this_object());
    i = sizeof(inv2);
    n = 0;
    i--;
    while(i > -1) {
    	if((int)inv2[i]->query_wood() > n) {
    		n = (int)inv2[i]->query_wood();
    		big = inv2[i]
;
    	}
    	i--;
    }
    return big;
}

int filter_weapon(object item, string type) {
  if(!item->id("weapon blank")) return 0;
  if(!item->query_property("progress "+name)) return 0;
  if((string)item->query_property("progress "+name) != type) return 0;
  return 1;
}

void skill_func(object from, object at, string arg) {
  object *inv, tmp;
  int time, qual, mod,wood_req;
  seteuid(getuid());
  arg = lower_case(arg);
  if(member_array(arg, METAL + BOTH) >= 0) {
    if(member_array(arg, BOTH) >= 0 && (int)from->query_skill("carpentry") <=
        0) {
      message("info", "Since this weapon has wooden componenets, you must also "+
            "have carpentry skill to forge it.", from);
      remove();
      return;
    }
    name = (string)from->query_name();
    inv = filter_array(all_inventory(from), "filter_weapon",
      this_object(), arg);
    if(sizeof(inv)) at = inv[0];
    if(!at->id("weapon blank")) {
      message("info", "You must use this skill on a weapon blank.", from);
      remove();
      return;
    }
    if(!present("greater forge", environment(from))) {
      message("info", "You must be in a room with a greater forge to use this skill!",
          from);
      remove();
      return;
    }
    if(member_array(arg, BOTH) >= 0) {
    	if(find_greatest_board(from)) {
    		board = find_greatest_board(from);
    	} else {
    		message("info","You need a board in your inventory to make this "+
    			"weapon type.",from);
    		remove();
    		return;
    	}
    	mod = (int)from->query_skill("carpentry");
    	mod = ((mod+1)/16)+3;
    } else {
    	mod = props["skill level"]/16 + 1;
    }
    tmp = new("/d/damned/virtual/"+arg+"_2.weapon");
    time = (725 + 3*(int)tmp->query_value()) / mod;
    if(member_array(arg, BOTH) >= 0) {
    	wood_req = (int)tmp->query_property("wood needed");
    }
    tmp->remove();
    tmp = new("/wizards/diewarzau/obj/misc/ingot");
    tmp->set_material(replace_string((string)at->query_material(), "/", "", 1));
    time *= to_int(pow(to_float((int)tmp->query_value()/10), 0.4));
    tmp->remove();
    if(member_array(arg, BOTH) >= 0) {
    	if(wood_req > (int)board->query_wood()) {
    		message("info","Your largest board is too small for this weapon "+
    			"type.",from);
    		remove();
    		return;
    	}
    }
    at->set_property("progress "+name, arg);
    qual = props["skill level"]/24 + 1 + random(2+props["skill level"]/26);
    if(qual < 0) qual = 0;
    if(qual > 6) qual = 6;
    name = sprintf("%s_%d", arg, qual);
    type = "weapon";
    set_work_message("%^CYAN%^You pound on the weapon blank.");
    time /= 2;
    start_work(at, from, time);
    return;
  }
  message("info", "See 'help weapons' for the weapons you can forge.",
      from);
  remove();
  return;
}

void finish_work(object from, object at) {
  object ob, ob2, ob3;
  float valf;
  int val;
  seteuid(getuid());
  if(member_array(what, BOTH) >= 0) {
  	if(!present(board,from)) {
  		if(!find_greatest_board(from)) {
  			message("info","You no longer have a board in your inventory! You "+
  				"fail to build your weapon.",from);
  			remove();
  			return;
  		}
  		board = find_greatest_board(from);
  	}
  }	
  ob = new("/d/damned/virtual/"+name+"."+type);
  if (member_array(what, BOTH) >= 0) {
  	if((int)board->query_wood() < (int)ob->query_property("wood needed")) {
  		message("info","%^CYAN%^You no longer have enough wood in your inventory to "+
  			"complete the weapon. Your skill fails.",from);
  		remove();
  		ob->remove();
  		return;
  	} else {
  		board->add_wood(-(int)ob->query_property("wood needed"));
  	}
  }
  message("info", "%^CYAN%^You are finished forging!", from);
  ob2 = new("/std/Object");
  ob2->set_material("metal/iron");
  ob3 = new("/std/Object");
  ob3->set_material(replace_string((string)at->query_material(), "/", "", 1));
  ob->move(from);
   if(!present(ob,from)) {
  	message("info","%^CYAN%^You cannot carry your creation so it falls to the ground.",
  		from);
  	ob->move(environment(from));
  }
  if(ob->query_value()) {
    val = (int)ob->query_value();
    val = val * (int)ob3->prop("value") / (int)ob2->prop("value");
    val = val/350;
    ob->set_value(val);
    from->add_exp2(1000 + val);
  } else if(ob->query_float_value() && (float)ob->query_float_value() > 0.0) {
    valf = (float)ob->query_float_value();
    valf *= to_float((int)ob3->prop("value")) / to_float((int)ob2->prop("value"));
    ob->set_float_value(valf);
    from->add_exp2(975);
  }
  ob2->remove();
  ob3->remove();
  ob->set_property("extra long","This weapon was forged by: "+from->query_cap_name());
  ob->set_material(replace_string((string)at->query_material(), "/", "", 1));
  if(intp(ob->prop("hardness")))
    ob->set_decay_rate((int)ob->prop("hardness"));
  at->remove();
  remove();
  return;
}

