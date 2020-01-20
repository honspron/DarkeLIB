// /wizards/excelsior/misc/weapon_pet


inherit "/std/pet";

object parent;

void create() { 
	::create();
	set_save(0);
	set_attack(1);
	set_carry(0);
	set_can_change_aggr(1);
}

void set_parent(object who) { parent = who; }

object query_parent() { return parent; }

void set_expire(int i) {
	call_out("go_away",i);
}

void go_away() {
	message("info","%^BOLD%^%^ORANGE%^The life leaves the living weapon "+
		"and it returns to its normal "+
		"state.",environment());
	parent->move(environment());
	parent->repair(-(query_max_hp() - query_hp()));
	parent->decay();
	remove();
}

void die(object ob) {
  message("other_action", query_cap_name()+
                 " drops %^RED%^dead%^RESET%^ before you.",
                 environment(this_object()),
                 ({ this_object() }));
  go_away();
}

string query_short() {
	string fname;
	fname = file_name(parent);
	if(strlen(fname) < 17 || fname[0..16] != "/d/damned/virtual")
		return capitalize(query("short"));
	return capitalize(article(query("short")));
}
		
