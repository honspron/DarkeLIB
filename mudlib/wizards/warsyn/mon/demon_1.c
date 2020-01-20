inherit "/std/pet";

void create() {
  ::create();
  set_name("Demon");
  set_combat_chance(100);
  set_id(({ "demon", "Demon" }));
  set("race", "human");
  set_body_type("winged-humanoid");
  set_attack(1);
  set_can_change_aggr(1);
  set_carry(0);
  set_save(1);
  set_level(25);
  set_exp(10000000);
  set_overall_ac(150);
  set_short("Demon from beyond the Pale");
  set_long("This creature is constantly warping and changing.  You "
  "can't tell what its true form is.");
  set_exp(10000000);
  set_property("physical resistance",
               ([ "default" : 95, "iron" : 95, "steel" : 95, "wood" : 95,
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
set_max_hp( 10000 );
  set_hp( 10000 );
  set_skill("melee", 140);
  set_skill("dodge", 110);
  set_skill("parry",  110);
  set_stats("strength",  300);
  set_property("melee damage", ([ "impaling" : 70 ]) );
  set_stats("intelligence", 98);
  set_skill("elementalism", 113);
  set_skill("chaos lore", 100);
  set_skill("necromancy", 140);
  set_mp(10000);
  set_spell_level("lifesteal", 6);
  add_spell("lifesteal", "$A");
  add_spell("greater elemental strike", "$A");
  set_spell_level("greater elemental strike", 6);
  return;
}

string query_element() { return "chaos"; }

void set_dur(int dur) {
  call_out("remove_servant", dur);
  return;
}

void remove_servant() {
  this_object()->force_me("drop all");
  message("info", "%^GREEN%^%^BOLD%^A Demon winks out of existence.",
          environment());
  remove();
return;
}
