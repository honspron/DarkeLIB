inherit "/std/pet";

void create() {
  ::create();
  set_name("Imp");
  set_combat_chance(100);
  set_id(({ "imp", "Imp" }));
  set("race", "human");
  set_body_type("winged-humanoid");
  set_attack(1);
  set_can_change_aggr(1);
  set_carry(0);
  set_save(1);
  set_level(18);
  set_exp(1500000);
  set_overall_ac(150);
  set_property("enhance criticals",-3);
  set_skill("resist stun", 150);
  set_short("Tall Imp");
  set_long("This ugly thing is deformed and mutated.  It has "
  "extremely long arms and legs.  Its face is twisted in a stupid grin.");
  set_property("physical resistance",
               ([ "default" : 30, "iron" : 30, "steel" : 30, "wood" : 30,
                    "silver" : -20 ]));
  set_aggr_status(0);
  return;
}

void set_owner(string who) {
  object ob;

  ob = find_player(who);
  if(!ob) {
    ::set_owner(who);
    return;
  }
  set_languages(({ "undead-tongue", "common", "elvish", "dwarvish", "serra",
"yin", "treefolk",
                 (string)ob->query_primary_lang() }) );
  ::set_owner(who);
  return;
}


void set_up(int pow) {
set_max_hp( 5000 );
  set_hp( 5000 );
  set_skill("melee", 150);
  set_skill("dodge", 80);
  set_skill("parry",  70);
  set_stats("strength",  150);
  set_property("melee damage", ([ "disruption" : 50 ]) );
  set_stats("intelligence", 40);
  set_skill("elementalism", 78);
  set_skill("chaos lore", 100);
  set_mp(10000);
  add_spell("elemental curse", "$A");
  set_spell_level("elemental curse", 6);
  return;
}

string query_element() { return "chaos"; }

void set_dur(int dur) {
  call_out("remove_servant", dur);
  return;
}

void remove_servant() {
  this_object()->force_me("drop all");
  message("info", "%^GREEN%^%^BOLD%^A Imp winks out of existence.",
          environment());
  remove();
return;
}
