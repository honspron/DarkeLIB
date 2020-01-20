// Coder: %^GREEN%^nEv!N%^RESET%^
// Darkemud
// Nihil, thralls spawned by the breeding pit
// 10/02/96

inherit "/std/pet";

void create() {
  	::create();
  	set_name("nihil");
   	set_id(({ "nihil" }));
  	set("race", "demon");
  	set_body_type("human");
  	set_attack(1);
  	set_carry(0);
  	set_save(1);
  	set_level(13);
	set_max_hp(1000);
	set_hp(1000);
	set_overall_ac(10);
	set_body_type("sphere");
  	set_short("%^BLUE%^%^BOLD%^cloud of darkness%^RED%^%^BOLD%^");
  	set_long("It is a hole in the existence of this multi-universe.");
  	set_aggr_status(0);
	call_out("destroy_me", 3600);
  	return;
}

void destroy_me() { TO->die(); }

void die(object who) {
	message("info", "%^BLUE%^%^BOLD%^A cloud of darkness fades away into "
		"nothingness...%^RESET%^", ENV(TO));
	::die(who);
	return;
}

void heart_beat() {
	object who;
	::heart_beat();
	who = TO->query_current_attacker();

	if(!who) return;
	if(!present(who)) return;
	if(random(100) < 10) {
		if(who->query_level() > random(50) ) { return ; }
		message("info", "You hear a voice in your head...you begin "
			"to feel very weak...'You are nothing...You are "
			"nothing...You are nothing...'", who);
		message("info", who->query_cap_name()+" grimaces in pain.",
			ENV(who), ({who}) );
		who->add_hp(-10);
		who->add_mp(-30);
		who->add_exp(-100);
		return;
	}
}

void set_owner(string who) {
	object ob;

	ob = find_player(who);
	if(!ob) {
		::set_owner(who);
		return;
	}
	set_languages( ({"yin", (string)ob->query_primary_lang() }) );
	::set_owner(who);
	return;
}

void set_up() {
// the nihil has an incoporeal body
	set_property("physical resistance", ([ "default": 90 ]) );
  	set_property("melee damage", ([ 
		"vacuum" : 30
	]) );
  	return;
}
