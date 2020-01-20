/*
 * Function handler for clan teaching of skills/spells.
 *
 * Diewarzau 7/16/96
 * DarkeLIB 1.0
 */

#include <daemons.h>
#include <clan.h>

int sk_dev_cost(object who, string skill, int flag);
int sp_dev_cost(object who, string skill, int flag);
int skill_level(string skill);
int calc_skill_inc(object tp, string skill);
int check_spell_level(object tp, string spell);
int check_skill_level(object tp, string skill);
int check_related_spell(string spell, object tp);
int check_related_skill(string skill, object tp);
int spell_level(string spell);
int skill_prereq_check(object who, string skill);
int spell_prereq_check(object who, string spell);

int capacity();

void create() {
  seteuid(getuid());
  return;
}

int check_skill_level(object tp, string skill) {
  int elevel = (int)tp->query_level();
  int newskill;

  newskill = (int)tp->query_base_skill(skill) +
    calc_skill_inc(tp, skill);
  if(newskill > 90) return 0;
  switch(newskill) {
  case -1000..60:
  default:
    elevel -= 10;
    break;
  case 61..75:
    elevel -= 15;
    break;
  case 76..91:
    elevel -= 20;
    break;
  }
  if(elevel < skill_level(skill)) return 0;
  return 1;
}

int check_spell_level(object tp, string spell) {
  int elevel = (int)tp->query_level();
  int newspell;
  int spell_lev;
  string spell_file = sprintf("/std/spells/%s",
			      replace_string(spell, " ", "_"));

  if(!file_exists(spell_file+".c")) return 0;
  spell_lev = (int)spell_file->query_property("spell level");
  newspell = (int)tp->query_base_spell(spell) + 1;
  if(newspell > 5) return 0;
  switch(newspell) {
  case -1000..3:
  default:
    elevel -= 10;
    break;
  case 4..4:
    elevel -= 15;
    break;
  case 5..5:
    elevel -= 20;
    break;
  }
  if(elevel < spell_lev) return 0;
  return 1;
}

int help_teach(string arg) {
  string tmp;
  int sz;

  sz = (int)this_player()->getenv("SCREEN");
  if(!sz) sz = 75;
  if(arg != "teach") return 0;
  tmp =
    "In order to teach someone a skill or spell, several minutes are "
    "often necessary.  During this time, neither the teacher nor the "
    "student may move, or the teaching will be interrupted.\n\n"
    "To teach a skill:\n"
    "teach skill <skill> to <whom>\n"
    "Ex: teach skill blade to diewarzau\n"
    "Cost: 5x normal dev cost (3x for related skills)\n"
    "      20 mithril per skill level.\n"
    "      skill level = (dev cost + fast dev/2) /4 (round down)\n"
    "\n"
    "To teach a spell:\n"
    "teach spell <spell> to <whom>\n"
    "Ex: teach spell fireball to diewarzau\n"
    "Cost: 5x normal dev cost (3x for related spells)\n"
    "      100 mithril per spell level * level learned.\n"
    "      Ex: 20th level spell to *6 costs 12000 mith (20 * 100 * 6)\n"
    "\n"
    "NOTE: You may only teach a skill up to (your skill) - 25% or any spell "
    "up to (your power) - *1.\n"
    "NOTE: Reagrdless of your teaching room level, you must learn skills "
    "and spells according to the table below:\n"
    "\n"
    "Max Skill Lev    Max Spell Lev     Your effective level\n"
    "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n"
    "60%              *3                your lev - 10\n"
    "75%              *4                your lev - 15\n"
    "90%              *5                your lev - 20\n"
    "\n"
    "For example, say a skill/spell is level 12 (spell level is in the spell "
    "help and skill level may be calculated as above).  If you want to learn the "
    "skill from 0-60% (or spell from *1-*3), you have to be level 22 (12 + 10).  "
    "To learn it up to 75% (or *4), you need to be level 27 (12 + 15)., and to learn it "
    "to 90% (or *5), you need to be level 32 (12 + 20).  The level of the TEACHER does "
    "not matter.\n"
    "%^RED%^Important!%^RESET%^ You are limited in the amount of total crosstraining \n"
    " you can receive\n"
    "Type capacity to find out roughly how much more you can learn.\n";
  this_player()->more(explode(wrap(tmp, sz), "\n"));
  return 1;
}

int check_related_skill(string skill, object tp) {
  string *all_skills, *dir, *guilds;
  string p_class;
  int i;

  p_class = (string)tp->query_class();
  dir = map_array(get_dir("/d/damned/guilds/"+p_class+
			  "/*.c"), (: $2 + $1 :), "/d/damned/guilds/"+p_class+"/");
  dir = filter_array(dir, (: call_other :),
		     "is_skill_room");
  all_skills = ({});
  i = sizeof(dir);
  while(i--)
    all_skills += (string *)dir[i]->query_all_skills();
  if(member_array(skill, all_skills) >= 0) return -1;
  if(!file_exists("/d/damned/guilds/join_rooms/"+
		  p_class+"_join.c")) {
    write("Error: Unable to find your join room.");
    return 0;
  }
  guilds = distinct_array((string *)call_other("/d/damned/guilds/join_rooms/"+
					       p_class+"_join", "query_related_guilds"));
  if(!guilds || !sizeof(guilds)) return 0;
  dir = ({});
  all_skills = ({});
  i = sizeof(guilds);
  while(i--)
    dir += filter_array(map_array(get_dir("/d/damned/guilds/"+guilds[i]+"/*.c"),
				  (: $2 + $1 :), "/d/damned/guilds/"+guilds[i]+"/"), (: call_other :),
			"is_skill_room");
  i = sizeof(dir);
  while(i--) all_skills += (string *)dir[i]->query_all_skills();
  if(member_array(skill, all_skills) >= 0) return 1;
  return 0;
}

int check_related_spell(string spell, object tp) {
  string *all_spells, *dir, *guilds;
  string p_class;
  int i;
  
  p_class = (string)tp->query_class();
  dir = map_array(get_dir("/d/damned/guilds/"+p_class+
			  "/*.c"), (: $2 + $1 :), "/d/damned/guilds/"+p_class+"/");
  dir = filter_array(dir, (: call_other :),
		     "is_spell_room");
  all_spells = ({});
  i = sizeof(dir);
  while(i--)
    all_spells += (string *)dir[i]->query_all_spells();
  if(member_array(spell, all_spells) >= 0) return -1;
  if(!file_exists("/d/damned/guilds/join_rooms/"+
		  p_class+"_join.c")) {
    write("Error: Unable to find your join room.");
    return 0;
  }
  guilds = distinct_array((string *)call_other("/d/damned/guilds/join_rooms/"+
					       p_class+"_join", "query_related_guilds"));
  if(!guilds || !sizeof(guilds)) return 0;
  dir = ({});
  all_spells = ({});
  i = sizeof(guilds);
  while(i--)
    dir += filter_array(map_array(get_dir("/d/damned/guilds/"+guilds[i]+"/*.c"),
				  (: $2 + $1 :), "/d/damned/guilds/"+guilds[i]+"/"), (: call_other :),
			"is_spell_room");
  i = sizeof(dir);
  while(i--) all_spells += (string *)dir[i]->query_all_spells();
  if(member_array(spell, all_spells) >= 0) return 1;
  return 0;
}

void abort_learning(object who) {
  object teach = (object)who->query("learning from");
  int idx;
  object ob;

  if(!teach) {
    who->set("learning from", 0);
    message("info", "%^CYAN%^The teaching is interrupted!", who);
    return;
  }
  idx = (int)teach->query("teaching idx");
  remove_call_out(idx);
  message("info", "%^CYAN%^You leave the teaching session.",
	  who);
  message("info","%^CYAN%^"+(string)who->query_cap_name()+
	  " interrupts your teaching efforts.", teach);
  who->set("learning from", 0);
  teach->set("teaching to", 0);
  teach->set("teaching idx", 0);
  return;
}

void abort_teaching(object who) {
  object learn = (object)who->query("teaching to");
  object ob;
  int idx = (int)who->query("teaching idx");

  if(!learn) {
    remove_call_out(idx);
    who->set("teaching to", 0);
    who->set("teaching idx", 0);
    return;
  }
  message("info", "%^CYAN%^You interrupt your teaching efforts.",
	  who);
  message("info", "%^CYAN%^"+(string)who->query_cap_name()+
	  " stops teaching you.", learn);
  who->set("teaching to", 0);
  remove_call_out(idx);
  who->set("teaching idx", 0);
  learn->set("learning from", 0);
  if(ob=(object)learn->query("learn shadow"))
    ob->external_destruct(ob);
  return;
}

int calc_skill_inc(object who, string skill) {
  int base;

  if(!who || !skill) return 0;
  base = (int)who->query_base_skill(skill);
  switch(base) {
  case 0..25:
    return 5;
  case 26..40:
    return 3;
  case 41..59:
    return 2;
  case 60..10000:
    return 1;
  }
  return 1;
}

int skill_level(string skill) {
  string file = sprintf("/std/skills/%s",
			replace_string(skill, " ", "_"));
  int dev, fdev;

  if(!file_exists(file+".c")) return 0;
  if(file->query_property("no crosstrain")) return 0;
  dev = (int)file->query_dev();
  fdev = (int)file->query_fast_dev();
  return (dev + fdev/2)/4;
}

int spell_level(string spell) {
  string file = sprintf("/std/spells/%s",
			replace_string(spell, " ", "_"));
  int dev, fdev;

  if(!file_exists(file+".c")) return 0;
  if(file->query_property("no crosstrain")) return 0;
  return (int)file->query_property("spell level");
}

int sk_dev_cost(object who, string skill, int flag) {
  string file;
  int times, mult, cost;
  int subt = (int)who->query_property("dev cost");

  if(!who || !who->is_player()) return 0;
  if(!skill) return 0;
  if(flag)
    mult = 2;
  else
    mult = 5;
  if((int)who->query_base_skill(skill) >= 80) mult *= 2;
  if((int)who->query_base_skill(skill) >= 100) mult *= 2;
  if((int)who->query_base_skill(skill) >= 150) mult *= 2;
  file = "/std/skills/"+replace_string(skill, " ", "_")+".c";
  if(!file_exists(file)) return 0;
  file = replace_string(file, ".c", "");
  times = (int)who->query_dev_times(skill, (int)who->query_level());
  if(!times) cost = (mult * (int)file->query_dev());
  else cost = (mult * times * (int)file->query_fast_dev());
  if(subt < 0) cost += subt;
  if(cost < 1) cost = 1;
  return cost;
}

int sp_dev_cost(object who, string skill, int flag) {
  string file;
  int spell_lev, times, mult, cost;
  int subt = (int)who->query_property("dev cost");

  if(!who || !who->is_player()) return 0;
  spell_lev = (int)who->query_base_spell(skill) + 1;
  if(!skill) return 0;
  if(spell_lev > 6) return 0;
  if(flag)
    mult = 2;
  else
    mult = 5;
  file = "/std/spells/"+replace_string(skill, " ", "_")+".c";
  if(!file_exists(file)) return 0;
  file = replace_string(file, ".c", "");
  times = who->query_spell_dev_times(skill, (int)who->query_level());
  if(!times) cost = (mult * spell_lev * (int)file->query_property("dev cost"));
  else cost = (spell_lev * mult * times * (int)file->query_property(
               "fast dev cost"));
  if(subt < 0) cost += subt;
  if(cost < 1) cost = 1;
  return cost;
}

int capacity()
{
int upurecap, upure;
upure = (int)this_player()->query_property("UNPURE");

    switch((int)environment(this_player())->query_room_info("teach room")) {
    case 1:
      upurecap = 500;
      break;
    case 2:
      upurecap = 700;
      break;
    case 3:
      upurecap = 1000;
      break;
    default:
      write("You need to be in a teaching room to teach a skill.");
      return 1;
}

switch(upurecap - upure)
{
	case 1..30 :
	      write("You know nearly all that can be learned here.");
	      break;
	case 31..90 :
	      write("Very little left.");
	      break;
	case 91..150 :
	      write("Little left.");
	      break;
	case 151..220 :
	      write("Some left.");
	      break;
	case 221..280 :
	      write("You should be able to learn some.");
	      break;
	case 281..441 :
	      write("You will be able to learn quite a bit more.");
	      break;
	case 442..642 :
	      write("You have just begun to learn here.");
	      break;
	case 643..740 :
	      write("So much room, so little time.");
	      break;
	case 741..850 :
	      write("There is vast potential.");
	      break;
	case 851..1000 :
	      write("You don't need to ask.");
	      break;
	default :
		write("You have maximized your learning in this teaching room.");
		return 1;
	}

return 1;

}

int teach_skill(string str) {
  string skill, to;
  int tlevel, time, flag, bucka, upurecap;
  object ob, who;

  if(sscanf(str, "skill %s to %s", skill, to) == 2) {
    if(!(who=present(lower_case(to), environment(this_player())))) {
      write("Could not find '"+to+"' here.");
      return 1;
    }
    skill = lower_case(skill);
    if((int)this_player()->query_base_skill(skill) <= 25) {
      write("Your base skill must be higher than 25% to teach."
	    "\nType 'skills base' to list base skill levels.");
      return 1;
    }
    if(!skill_level(skill)) {
      write("That skill either does not exist or you cannot crosstrain it.");
      return 1;
    }

    if((string)who->query_guild() != 
       (string)this_player()->query_guild()) {
      write("You may only teach skills to members of your clan.");
      return 1;
    }

    if(CLAN_D->test_member_priv((string)who->query_guild(),
      (string)who->query_name(), NO_TEACH)) {
      write((string)who->query_cap_name()+ " is not allowed to learn here, orders "
        "of the clan leader.");
      return 1;
    }
    if(this_player()->query("teaching to")) {
      message("info", "You cannot teach more than one skill/spell at a time.",
	      this_player());
      return 1;
    }
    if(!skill_prereq_check(who, skill))
    {
      write((string)who->query_cap_name()+ " does not have the prerequisite for that.");
      return 1;
    }
    if(who->query("learning from")) {
      write((string)who->query_cap_name()+ " is already learning a skill.");
      return 1;
    }
    tlevel = (int)this_player()->query_base_skill(skill) - 25;
    switch((int)environment(this_player())->query_room_info("teach room")) {
    case 1:
      if(tlevel > 60) tlevel = 60;
      time = 120;
      upurecap = 500;
      break;
    case 2:
      if(tlevel > 75) tlevel = 75;
      time = 60;
      upurecap = 700;
      break;
    case 3:
      if(tlevel > 90) tlevel = 90;
      time = 30;
      upurecap = 1000;
      break;
    default:
      write("You need to be in a teaching room to teach a skill.");
      return 1;
    }
    if(tlevel <= (int)who->query_base_skill(skill)) {
      write((string)who->query_cap_name()+" has already learned "+
	    "all that "+nominative(who)+" can about that skill.");
      return 1;
    }
    if(!check_skill_level(who, skill)) {
      write((string)who->query_cap_name()+" cannot learn any more "+
	    "on that skill at "+possessive(who)+" level.");
	    return 1;
    }
    if((int)who->query_property("UNPURE") >= upurecap)
	{
          write((string)who->query_cap_name()+" cannot learn any more "+
	    "in this teaching room.");
	    return 1;
	}
    ob = new("/std/spells/shadows/move_shadow");
    ob->set_move_func((: call_other, this_object(), "abort_teaching" :));
    ob->set_move_arg(this_player());
    ob->start_shadow(this_player());
    ob = new("/std/spells/shadows/move_shadow");
    ob->set_move_func((: call_other, this_object(), "abort_learning" :));
    ob->set_move_arg(who);
    ob->start_shadow(who);
    who->set("learning from", this_player());
    this_player()->set("teaching to", who);
    if(check_related_skill(skill, who))
      flag = 1;
    else
      flag = 0;
    if((int)who->query_money("mithril") <
       skill_level(skill) * 20) {
      write((string)who->query_cap_name()+
	    " must have "+sprintf("%d mithril ",
				  skill_level(skill) * 20)+
	    "to train that skill.");
      ob->external_destruct(ob);
      who->set("learning from", 0);
      this_player()->set("teaching to", 0);
      return 1;
    }
    if((int)who->query_property("dev points") <
       sk_dev_cost(who, skill, flag)) {
      write((string)who->query_cap_name()+
            " must have "+sprintf("%d dev points ",
				  sk_dev_cost(who, skill, flag))+
	    "to train that skill.");
      ob->external_destruct(ob);
      who->set("learning from", 0);
      this_player()->set("teaching to", 0);
      return 1;
    }
    this_player()->set("teaching idx", call_out("finish_teach_skill", time,
						this_player(), who, skill,
						tlevel, flag));
    write("%^CYAN%^You begin teaching the skill...");
    message("info", "%^CYAN%^"+(string)this_player()->query_cap_name()+
	    " begins teaching you the skill: %^RESET%^"+skill+".",
	    who);
    if(flag)
      message("info", "Related skill.  2x cost only.", who);
    return 1;
  } else if(sscanf(str, "spell %s to %s", skill, to) == 2) {
    if(!(who=present(lower_case(to), environment(this_player())))) {
      write("Could not find '"+to+"' here.");
      return 1;
    }
    skill = lower_case(skill);
    if((int)this_player()->query_base_spell(skill) <= 4) {
      write("Your base spell level must be *5 or above to teach a spell.");
      return 1;
    }
    if(!spell_level(skill)) {
      write("That spell either does not exist or you cannot crosstrain it.");
      return 1;
    }
    if((string)who->query_guild() != 
       (string)this_player()->query_guild()) {
      write("You may only teach spells to members of your clan.");
      return 1;
    }
    if(CLAN_D->test_member_priv((string)who->query_guild(),
      (string)who->query_name(), NO_TEACH)) {
      write((string)who->query_cap_name()+ " is not allowed to learn here, orders "
        "of the clan leader.");
      return 1;
    }
    if(this_player()->query("teaching to")) {
      message("info", "You cannot teach more than one skill/spell at a time.",
	      this_player());
      return 1;
    }
    if(!spell_prereq_check(who, skill))
    {
      write((string)who->query_cap_name()+ " does not have the prerequisite for that.");
      return 1;
    }

    if(who->query("learning from")) {
      write((string)who->query_cap_name()+ " is already learning a spell or skill.");
      return 1;
    }
    tlevel = (int)this_player()->query_base_spell(skill) - 1;
    switch((int)environment(this_player())->query_room_info("teach room")) {
    case 1:
      if(tlevel > 3) tlevel = 3;
      time = 600;
	upurecap = 500;
      break;
    case 2:
      if(tlevel > 4) tlevel = 4;
      time = 360;
        upurecap = 700;
      break;
    case 3:
      if(tlevel > 5) tlevel = 5;
      time = 180;
        upurecap = 1000;
      break;
    default:
      write("You need to be in a teaching room to teach a spell.");
      return 1;
    }
    if(tlevel <= (int)who->query_base_spell(skill)) {
      write((string)who->query_cap_name()+" has already learned "+
	    "all that "+nominative(who)+" can about that spell from you at this time.");
      return 1;
    }
    if(!check_spell_level(who, skill)) {
      write((string)who->query_cap_name()+" cannot learn any more "+
	    "on that spell at "+possessive(who)+" level.");
	    return 1;
    }
    if((int)who->query_property("UNPURE") >= upurecap)
	{
          write((string)who->query_cap_name()+" cannot learn any more "+
	    "in this teaching room.");
	    return 1;
	}

    ob = new("/std/spells/shadows/move_shadow");
    ob->set_move_func((: call_other, this_object(), "abort_teaching" :));
    ob->set_move_arg(this_player());
    ob->start_shadow(this_player());
    ob = new("/std/spells/shadows/move_shadow");
    ob->set_move_func((: call_other, this_object(), "abort_learning" :));
    ob->set_move_arg(who);
    ob->start_shadow(who);
    who->set("learning from", this_player());
    this_player()->set("teaching to", who);
    if(check_related_spell(skill, who))
      flag = 1;
    else
      flag = 0;
    bucka = 100 * spell_level(skill) * ((int)who->query_base_spell(skill)+1);
    if((int)who->query_money("mithril") < bucka) {
      write((string)who->query_cap_name()+
	    " must have "+sprintf("%d mithril ",
				  bucka)+
	    "to train that spell.");
      ob->external_destruct(ob);
      who->set("learning from", 0);
      this_player()->set("teaching to", 0);
      return 1;
    }
    if((int)who->query_property("dev points") <
       sp_dev_cost(who, skill, flag)) {
      write((string)who->query_cap_name()+
            " must have "+sprintf("%d dev points ",
				  sp_dev_cost(who, skill, flag))+
	    "to train that spell.");
      ob->external_destruct(ob);
      who->set("learning from", 0);
      this_player()->set("teaching to", 0);
      return 1;
    }
    this_player()->set("teaching idx", call_out("finish_teach_spell", time,
						this_player(), who, skill,
						tlevel, flag));
    write("%^CYAN%^You begin teaching the spell...");
    message("info", "%^CYAN%^"+(string)this_player()->query_cap_name()+
	    " begins teaching you the spell: %^RESET%^"+skill+".",
	    who);
    if(flag)
      message("info", "Related spell.  2x cost only.", who);
    return 1;
  }
  else {
    write("Teach what?  See 'help teach' for syntax.");
    return 1;
  }
}

void finish_teach_skill(object teach, object learn, string skill, int tlevel, int flag) {
  int my_skill;

  if(!teach && learn) {
    message("info", "Could not find teacher.....aborting teach attempt.",
	    learn);
    learn->set("learning from", 0);
    return;
  }
  else if(teach && !learn) {
    message("info", "Could not find student.....aborting teach attempt.",
            learn);
    teach->set("teaching to", 0);
    teach->set("teaching idx", 0);
    return;
  }
  else if(!teach && !learn) return;
  learn->set("learning from", 0);
  teach->set("teaching to", 0);
  teach->set("teaching idx", 0);
  message("info", "%^CYAN%^Finished teaching!", ({ teach, learn }));
  if((int)learn->query_money("mithril") <
     20*skill_level(skill)) {
    message("info", "You do not have the required "+
	    sprintf("%d mithril, ", 20*skill_level(skill))+
	    "and the teaching attempt fails.",
	    learn);
    return;
  }
  if((int)learn->query_property("dev points")
     < sk_dev_cost(learn, skill, flag)) {
    message("info", "You do not have the required "+
	    sprintf("%d development points, ",
		    sk_dev_cost(learn, skill, flag))+
	    "and the teaching attempt fails.",
	    learn);
	  message("info", (string)learn->query_cap_name()+
	          " does not have the required mithril, and the "
	          "teaching attempt fails.", teach);
	  message("info", (string)learn->query_cap_name()+
	          " does not have the required dev points, and "
	          "the teaching attempt fails.", teach);
    return;
  }
  learn->add_money("mithril", -20*skill_level(skill));
  my_skill = (int)learn->query_base_skill(skill);
  my_skill += calc_skill_inc(learn, skill);
  if(my_skill >= tlevel) {
    my_skill = tlevel;
    message("info", "You have now learned the maximum skill level for "+
	    skill+" which may be taught to you by "+
	    (string)teach->query_cap_name(), learn);
  }
  learn->add_dev(-1 * sk_dev_cost(learn, skill, flag));
  learn->set_last_dev(skill, (int)learn->query_level());
  learn->set_skill(skill, my_skill);
  learn->set_property("UNPURE",learn->query_property("UNPURE")+skill_level(skill));
  write("You now have "+skill+" at "+sprintf("%d%%.", 
					     (int)learn->query_skill(skill)));
  return;
}

void finish_teach_spell(object teach, object learn, string spell, int tlevel, int flag) {
  int my_spell, bucka;

  if(!teach && learn) {
    message("info", "Could not find teacher.....aborting teach attempt.",
	    learn);
    learn->set("learning from", 0);
    return;
  }
  else if(teach && !learn) {
    message("info", "Could not find student.....aborting teach attempt.",
            learn);
    teach->set("teaching to", 0);
    teach->set("teaching idx", 0);
    return;
  }
  else if(!teach && !learn) return;
  learn->set("learning from", 0);
  teach->set("teaching to", 0);
  teach->set("teaching idx", 0);
  message("info", "%^CYAN%^Finished teaching!", ({ teach, learn }));
  bucka = 100 * spell_level(spell) * ((int)learn->query_base_spell(spell)+1);
  if((int)learn->query_money("mithril") <
     bucka) {
    message("info", "You do not have the required "+
	    sprintf("%d mithril, ", bucka)+
	    "and the teaching attempt fails.",
	    learn);
	  message("info", (string)learn->query_cap_name()+
	          " does not have the required mithril, and the "
	          "teaching attempt fails.", teach);
    return;
  }
  if((int)learn->query_property("dev points")
     < sp_dev_cost(learn, spell, flag)) {
    message("info", "You do not have the required "+
	    sprintf("%d development points, ",
		    sk_dev_cost(learn, spell, flag))+
	    "and the teaching attempt fails.",
	    learn);
	  message("info", (string)learn->query_cap_name()+
	          " does not have the required dev points, and "
	          "the teaching attempt fails.", teach);
    return;
  }
  learn->add_money("mithril", -1*bucka);
  my_spell = (int)learn->query_base_spell(spell) + 1;
  if(my_spell >= tlevel) {
    my_spell = tlevel;
    message("info", "You have now learned the maximum spell level for "+
	    spell+" which may be taught to you by "+
	    (string)teach->query_cap_name(), learn);
  }
  learn->add_dev(-1 * sp_dev_cost(learn, spell, flag));
  learn->set_last_spell_dev(spell, (int)learn->query_level());
  learn->set_spell_level(spell, my_spell);
  learn->set_property("UNPURE",learn->query_property("UNPURE")+(my_spell * spell_level(spell)) );
  write("You now have "+spell+" at "+sprintf("*%d.", 
					     (int)learn->query_spell_level(spell)));
  return;
}

int skill_prereq_check(object who, string skill)
{
object skillobby;
string prereq;
skillobby = find_object("/std/skills/"+replace_string(skill, " ", "_"));

if(!prereq = skillobby->query_property("prereq")) return 1;
if(who->query_base_skill(skill) >= who->query_base_skill(prereq)) return 0;
else return 1;
}

int spell_prereq_check(object who, string spell)
{
object spellobby;
string prereq;
spellobby = find_object("/std/spells/"+replace_string(spell, " ", "_"));

if(!prereq = spellobby->query_property("prereq")) return 1;
if(who->query_spell_level(spell) >= who->query_spell_level(prereq)) return 0;
else return 1;
}

