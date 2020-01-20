#include <std.h>

inherit MONSTER;

create() {
  ::create();
    set_name("monk");
    set_id( ({ "monk" }) );
    set_short("Elderly Monk");
     set("race", "high-man");
    set_long(@TEXT
This monk appears to be on duty to guard and protect the property
and belongings of the holy church.  He monitors the entry to the
sacred vault to the east and collects a tithe from those that pass.
TEXT
);
    set_body_type("human");
    set_level(18);
    set_skill("melee", 60);
    set_skill("dodge", 85);
    set_skill("parry", 80);
    set_skill("block", 75);
    set_skill("martial arts", 85);
    set_overall_ac(40);
    set_stats("strength", 300);
    set_max_hp(1200);
    set_hp(1200);
}

void init() {
  ::init();
  add_action("block_exit", "west");
  return;
}

int block_exit() {
  int gld;
  string p_name;
  object join_room, *inv;

  if(wizardp(this_player())) return 0;
   if((string)this_player()->query_class() != "cleric") {
     write("The Monk says in Common: Only priests of the faith may pass.");
    return 1;
  }
  inv = filter_array(all_inventory(this_player()), "locker_filter",
        this_object());
  if(sizeof(inv)) {
    write(@TEXT
The Monk says in Common: Our Lord will provide...thus there is no need
for storage devices to be brought into His sacred vault.
TEXT
);
    return 1;
  }
  join_room = find_object_or_load("/d/damned/guilds/join_rooms/cleric_join");
//  gld =  join_room->query_tithe() * (int)this_player()->query_level();
  gld =  5 * (int)this_player()->query_level();
  if((int)this_player()->query_money("silver") < gld) {
    write("The Monk says in Common: You are expected to tithe "+gld+" silver for passage.");
    return 1;
  }
  p_name = (string)this_player()->query_name();
  if(member_array("treasury restrict", (string *)join_room->
                  query_member_privs(p_name)) >= 0) {
    write("The Monk says in Common: A Holy writ lists you as forbidden to pass.");
    return 1;
  }
  write("The Monk says in Common: His will be done...a blessing on you.");
  this_player()->add_money("silver", -1*gld);
  this_object()->add_money("silver", gld);
  return 0;
}

int locker_filter(object item) { return (int)item->query_is_locker(); }

