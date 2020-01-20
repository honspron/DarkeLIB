#include <std.h>

inherit MONSTER;

create() {
  ::create();
    set_name("guard");
    set_id( ({ "guard" }) );
    set_short("A big, burly, badass, guard");
     set("race", "high-man");
    set_long(
   "The guard stands in front of the stairs. Warning! This guy will "+ 
    "waste anyone!");
    set_body_type("human");
    set_level(118);
    set_exp(3000000);
    set_overall_ac(340);
    set_max_hp(1200000);
    set_hp(1200000);
    set_property("handedness", "right hand");
    new("/d/damned/virtual/long-sword_6.weapon")->
      move(this_object());
    new("/d/damned/virtual/large-shield.armour")->
      move(this_object());
    new("/d/damned/virtual/chain-vest.armour")->
      move(this_object());
    new("/d/damned/virtual/iron-greaves.armour")->
      move(this_object());
    new("/d/damned/virtual/iron-bracer.armour")->
      move(this_object());
    new("/d/damned/virtual/iron-bracer.armour")->
      move(this_object());
    force_me("wear vest");
    force_me("wield sword in right hand");
    force_me("wear shield on left hand");
    force_me("wear greaves");
    force_me("wear bracer 2 on right arm");
    force_me("wear bracer on left arm");
}

void init() {
  ::init();
  add_action("block_exit", "up");
  return;
}

int block_exit() {

  if(wizardp(this_player())) return 0;
   if((string)this_player()->query_class() != "child") {
     write("The Guard says in Common: Only newbies may pass");
    return 1;
  }
  write("The Guard says in Common: You may pass.");
  return 0;
}
