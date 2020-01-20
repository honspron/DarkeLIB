#include <std.h>

inherit MONSTER;

create() {
  ::create();
    set_name("philip");
    set_id( ({ "philip", "cardinal", "cardinal philip", "man", "cleric", "priest" }) );
    set_short("Cardinal Philip");
     set("race", "high-man");
    set_long(@TEXT
Before you stands a Cardinal of the church.  His azure robes reflect
his rank and standing in the Holy Order.  His warm smile and relaxed
posture gives him a rather parental presence.
TEXT
);
    set_body_type("human");
    set_level(30);
    set_skill("prayer", 150);
    set_skill("body alteration", 150);
    set_skill("melee",200);
    set_skill("parry",150);
    set_skill("perception",150);
    set_skill("block", 75);
    set_skill("martial arts", 45);
    set_overall_ac(150);
    set_property("enhance criticals",-10);
    set_stats("strength", 300);
    set_max_hp(4200);
    set_hp(4200);

    set_combat_chance(75);
    set_casting_chance(90);

    add_spell("bolt of righteousness", "$A");
    set_spell_level("bolt of righteousness", 6);
    add_spell("instill poison", "$A");
    set_spell_level("instill poison", 6);

}

void init() {
  ::init();
  add_action("block_exit", "south");
  return;
}

int block_exit() {
  int gld;
  string p_name;
  object join_room, *inv;

  if(wizardp(this_player())) return 0;
  join_room = find_object_or_load("/d/damned/guilds/join_rooms/cleric_join");
//  gld =  join_room->query_tithe() * (int)this_player()->query_level();
  gld =  5 * (int)this_player()->query_level();
  if((int)this_player()->query_money("silver") < gld) {
    write("The Cardnal says in Common: You are expected to tithe "+gld+" silver for passage.");
    return 1;
  }
  write("The Cardnal says in Common: His will be done...a blessing on you.");
  this_player()->add_money("silver", -1*gld);
// #if 0
  present("box", environment(this_object()))->add_money("silver", gld);
// #endif
  return 0;
}

int locker_filter(object item) { return (int)item->query_is_locker(); }

