//  The AntiClinton



inherit "/std/monster";



int is_pet() { return 1; }



void create() {

  ::create();

  set_name("anticlinton");

  set_id(({ "clinton", "anti-clinton", "anticlinton",

    "the anticlinton" }));

  set_short("The AntiClinton");

  set_long("The AntiClinton seems very upset about the "

  "new bill Pres. Clinton signed calling for the restriction "

  "of 'indecent' material on the internet.");

  set_level(20);

  set_melee_damage(([ "crushing" : 45, "impact" : 45 ]));

  set_skill("conjuration", 75);

  set_spell_level("lightning bolt", 6);

  add_spell("lightning bolt", "$A");

  set_spell_level("blizzard", 4);

  add_spell("blizzard", "");

  set_combat_chance(100);

  set_speed(60);

  set_moving(1);

  return;

}



void init_shouts() {

  call_out("shout_once", 10);

  return;

}



void shout_once() {

  message("shout", "The AntiClinton shouts: "+

  "FUCK SHIT DAMN HELL PUSSY CUNT PRICK COCK JOHNSON MOTHER FUCKER AND SHIT!", users());

  call_out("shout_twice", 4);

  return;

}



void shout_twice() {

  message("shout", "The AntiClinton shouts: "+

    "Just say 'NO' to internet censorship.", users());

  call_out("shout_once", 600);

  return;

}



