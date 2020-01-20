#include <rooms.h>
#define STATS ({ "strength", "intelligence", "dexterity", \
"charisma", "wisdom", "constitution" })

inherit "std/room";

varargs int check_pts(object tp, int pts, int flag);

void create() {
   ::create();
   set_property("indoors",1);
   set_property("light",2);
   set("short","The Quest Room");
   set("long",
"This is the Adventurer's Quest Room.  Here you may find out what "
"quests are to be solved in this realm.  You may also trade quest "
"points for a variety of things.\n"
"\nThere is a sign on the east wall.");
   add_exit("/d/damned/akkad/ak_marksw", "east");
   set_items( (["sign": (: call_other, this_object(), "read_sign" :) ]) );
}

varargs int check_pts(object tp, int pts, int flag) {
  if((int)tp->query_quest_points() < pts) {
    message("info", "You do not have the "+pts+" quest points "+
            "required for that.", tp);
    return 0;
  }
  if(!flag)
    tp->add_quest_points(-1 * pts);
  return 1;
}

int read_sign() {
  write("The sign reads:\n");
  write("To find out what quests are available, type 'list quests'.");
  write("For help on spending you quest points, type 'help quest'.");
  return 1;
}

void init() {
  ::init();
  add_action("help_me", "help");
  add_action("quest_list", "list");
  add_action("quest_points", "purchase");
  return;
}

int quest_points(string str) {
  int num;
  object tp;

  tp = this_player();
  if(!str || !sscanf(str, "%d", num))
    return notify_fail("Usage: purchase #\n");
  switch(num) {
  case 1:
    if(!check_pts(tp, 1)) return 1;
     write("You recieve 75 dev points.");
    tp->add_dev(75);
    break;
  case 2:
    if(!check_pts(tp, 999999999)) return 1;
    write("You receive 100 mithril pieces.");
     tp->add_money("mithril", 100);
    break;
  case 3:
    if(tp->query_bless_num()) {
      write("You must wait until you blessing wears off.");
      return 1;
    }
    if((int)tp->query_property("luck") >= 8) {
      message("info", "You may not receive further luck.",
        tp);
      return 1;
    }
    if(!check_pts(tp, 12)) return 1;
    write("You receive +1% Luck.");
    tp->set_property("luck", 1 + (int)tp->
                     query_property("luck"));
    break;
  case 4:
    if(tp->query_bless_num()) {
      write("You must wait until you blessing wears off.");
      return 1;
    }
    if(5+(int)tp->query_property("luck") > 8) {
      message("info", "That would put you over 8% luck which is the maximum.",
        tp);
      return 1;
    }
    if(!check_pts(tp, 55)) return 1;
    write("You receive +5% Luck");
    tp->set_property("luck", 5 + (int)tp->
                     query_property("luck"));
    break;
//  case 5:
//    if(!check_pts(tp, 25, 1)) return 1;
//    write("Please choose a skill that you want at 50%.");
//    printf("Skill? ");
//    input_to("what_skill", 0, 50, 25);
//    break;
//  case 6:
//    if(!check_pts(tp, 60, 1)) return 1;
//    write("Please choose a skill that you want at 75%.");
//    printf("Skill? ");
//    input_to("what_skill", 0, 75, 60);
//    break;
//  case 7:
//    write("Please choose a spell that you want at lvl. 2.");
//    printf("Spell? ");
//    input_to("what_spell", 0, 2, 3);
//    break;
// case 8:
//    write("Please choose a spell that you want at lvl. 4.");
//   printf("Spell? ");
//    input_to("what_spell", 0, 4, 6);
//    break;
//  case 9:
//    write("Please choose a spell that you want at lvl. 6.");
//    printf("Spell? ");
//    input_to("what_spell", 0, 6, 10);
//    break;
  case 5:
    if((int)tp->query_base_skill("telepathy") > 50) {
      write("You already have telepathy higher than 50%.");
      return 1;
    }
    if(!check_pts(tp, 15)) return 1;
    tp->set_skill("telepathy", 50);
    write("You have 50% telepathy skill.");
    return 1;
  case 6:
    if((int)tp->query_base_skill("telepathy") > 80) {
      write("You already have telepathy higher than 80%.");
      return 1;
    }
    if(!check_pts(tp, 45)) return 1;
    tp->set_skill("telepathy", 80);
    write("You have 80% telepathy skill.");
    return 1;
  case 7:
    if(!check_pts(tp, 5)) return 1;
    tp->set_max_mp((int)tp->query_max_mp() + 10);
    write("You now have 10 more magic points.");
    return 1;
  case 8:
    if(!check_pts(tp, 4)) return 1;
    tp->set_max_hp((int)tp->query_max_hp() + 10);
    write("You now have 10 more hit points.");
    return 1;
  case 9:
    if(tp->query_property("magic resistance") > 29)
      return notify_fail("You cannot increase your magic resistance any higher here.\n");
    if(!check_pts(tp, 21)) return 1;
    if(!tp->query_property("magic resistance"))
      tp->set_property("magic resistance", 5);
    else
      tp->set_property("magic resistance", 5 +
            (int)tp->query_property("magic resistance"));
    write("You now have "+
        (int)tp->query_property("magic resistance")+
        "% magic resistance.");
    return 1;
  case 10:
    if(!check_pts(tp, 4)) return 1;
    write("Please choose a stat to raise (first 3 letters).");
    printf("Stat? ");
    input_to("what_stat");
    break;
  case 11:
    if(tp->query_property("limb regen")) {
      write("You already have limb regeneration!");
      return 1;
    }
    if(!check_pts(tp, 40)) return 1;
    tp->set_property("limb regen", 1);
    write("You now have limb regeneration.");
    break;
  case 12:
    if(!check_pts(tp, 15)) return 1;
    tp->add_sight_bonus(1);
    write("You receive +1 night vision.");
    break;
  case 13:
    if(tp->query_property("tough skin")) {
      write("You already have tough skin.");
      return 1;
    }
    if(!check_pts(tp, 20)) return 1;
    tp->set_property("natural ac",
      3 + (int)tp->query_property("natural ac"));
    tp->set_property("tough skin", 1);
    write("You now have tough skin.");
    break;
  case 14:
    if(tp->query_property("chitin")) {
      write("You already have chitin.");
      return 1;
    }
    if(!check_pts(tp, 40)) return 1;
    tp->set_property("natural ac",
      7 + (int)tp->query_property("natural ac"));
    tp->set_property("chitin", 1);
    write("You now have chitin.");
    break;
  case 15:
    if(tp->query_property("ambidextry")) {
      write("You are already ambidextrous.");
      return 1;
    }
    if(!check_pts(tp, 40)) return 1;
    tp->set_property("ambidextry", 1);
    write("You are now ambidextrous.");
    break;
  case 16:
    if(tp->query_metabolism()) {
      write("You must wait until your spell expires.");
      return 1;
    }
    if(!check_pts(tp, 35)) return 1;
    tp->set_property("extra heart beat",
      25 + (int)tp->query_property("extra heart beat"));
    write("Your metabolism is increased by 25%.");
    break;
  case 17:
    if(!check_pts(tp, 15)) return 1;
    tp->set_property("extra hp regen", 10 +
      (int)tp->query_property("extra hp regen"));
    write("Your healing rate is increased by 10%.");
    break;
  case 18:
    if(!check_pts(tp, 20)) return 1;
    tp->set_property("extra mp regen", 10 +
      (int)tp->query_property("extra mp regen"));
    write("Your mp regeneration rate is increased by 10%.");
    break;
  case 19:
    if((int)tp->query_property("dev cost") < -10) {
      write("You may not buy any more dev cost discount.");
      return 1;
    }
    if(!check_pts(tp, 12)) return 1;
    tp->set_property("dev cost", -1 +
      (int)tp->query_property("dev cost"));
    write("Your development cost for all skills/spells is reduced by 1.");
    break;
  }
  tp->save_player((string)tp->query_name());
  return 1;
}

int what_stat(string stat) {
  int i;

  stat = lower_case(stat);
  if((i=member_array(stat, STATS, 3)) < 0) {
    write("Please choose one of the available stats:");
    write("str, wis, con, dex, int, or cha.");
    input_to("what_stat");
    return 1;
  }
  this_player()->set_stats(STATS[i], (int)this_player()->query_base_stats(
          STATS[i]) + 1);
  write("You receive +1 "+STATS[i]+".");
  return 1;
}

/*
void what_spell(string skill, int lvl, int cost) {
  object ob;
  
  skill = lower_case(skill);
  if(!file_exists("/std/spells/"+replace_string(skill, " ", "_")+
                  ".c")) {
    write("'"+skill+"': No such spell.");
    return 1;
  }
  ob = new("/std/spells/"+replace_string(skill, " ", "_"));
  cost *= (int)ob->query_property("spell level");
  if(!check_pts(this_player(), cost)) return 1;
  if((int)this_player()->query_spell_level() >= lvl) {
    write("You already have that spell at a higher level!");
    return 1;
  }
  this_player()->set_spell_level(skill, lvl);
  write("You receive "+skill+" at *"+lvl+".");
  return 1;
}

void what_skill(string skill, int lvl, int cost) {
  skill = lower_case(skill);
  if(!file_exists("/std/skills/"+replace_string(skill, " ", "_")+
                  ".c")) {
    write("'"+skill+"': No such skill.");
    return 1;
  }
  if((int)this_player()->query_base_skill() > lvl) {
    write("You already have that skill at a higher level!");
    return 1;
  }
  this_player()->set_skill(skill, lvl);
  write("You receive "+skill+" at "+lvl+"%.");
  this_player()->add_quest_points(-1 * cost);
  return 1;
}
*/

int help_me(string str) {
  string help_str;
  
  if(!str || strlen(str) < 5 || str[0..4] != "quest")
    return 0;
  help_str =
"You may spend quest points on the following things:\n"
"\n"
"#  Item                              Cost (quest points):\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
"1.  50 development points            1\n"
"2.  50 mithril pieces                1\n"
"3.  +1% Luck (bonus to all skills)   12\n"
"4.  +5% Luck                         55\n"
"5.  50% telepathy skill              15\n"
"6.  80% telepathy skill              45\n"
"7.  +10 magic points (max)           5\n"
"8.  +10 hit points (max)             4\n"
"9.  +5% magic resistance             21\n"
"10. +1 to any stat                   4\n"
"11. Limb Regeneration                40\n"
"12. +1 night vision                  15\n"
"13. +3 AC (tough skin - once only)   20\n"
"14. +7 AC (chitin - once only)       40\n"
"15. Ambidextry (no offhand penalty)  40\n"
"16. 25% faster metabolism            55\n"
"17. 10% faster healing               15\n"
"18. 10% faster mp regeneration       20\n"
"19. Fast learning: -1 dev cost to    12\n"
"       everything!\n"
"\nType 'purchase #' to purchase an item.";
  this_player()->more(explode(help_str, "\n"));
  return 1;
}

int quest_list(string str) {
  int num;

  num = 0;
  if(!str || (!sscanf(str, "quest %d", num) && str != "quests"))
    return notify_fail("List what?\n");
  if(num) {
    ROOM_QUEST->list_quests(this_player(), num);
    return 1;
  }
  ROOM_QUEST->list_quests(this_player());
  write("\nType 'list quest #' to look at a particular quest.");
  return 1;
}






