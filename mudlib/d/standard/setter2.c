//      /d/st_adjndard/setter.c
//      Starting room for new characters choosing races
//      from the Nightmare Mudlib
//      created by Shadowwolf@Nightmare july 1992
//      modified by Descartes of Borg for the race daemon 10 june 1993

#include <std.h>
#include <security.h>
#include <rooms.h>
#include <daemons.h>
#include <ansi.h>

#define STATS ({ "strength", "constitution", "intelligence",\
		   "dexterity", "wisdom", "charisma" })
#define CLS ESC+"[H"+ESC+"[2J"

inherit ROOM;

string *tab_str = ({ "35-49   +1 point",
                    "50       0 points",
                    "51-75    1 point",
                    "76-85    2 points",
                    "86-95    3 points",
                    "96-100   4 points",
                    "101-105  5 points",
                    "106-110  6 points" });

string rand_choice =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

void do_rolls();
void assign_point(string str, int *points, int pts_left);
void pick_stat(string str, int *points, int pts_left);
void set_ansi();
int pt_to_stat(int pts);
string random_password(int len);

string random_password(int len) {
  string ret = "";
  int idx, ln;
  
  if(len <= 0) return "";
  ln = strlen(rand_choice);
  while(len--) {
    idx = random(ln);
    ret += rand_choice[idx..idx];
  }
  return ret;
}

int pt_to_stat(int pts) {
  pts += 15;
  switch(pts) {
  case 0..40:
    return 35+pts;
  case 41..60:
    return 75 + (pts - 40)/2;
  case 61..90:
    return 85 + (pts - 60)/3;
  case 91..110:
    return 95 + (pts - 90)/4;
  case 111..135:
    return 100 + (pts - 110)/5;
  case 136..10000:
   if(pts <= 166) return 105 + (pts - 135)/6;
    else return 110;
  default:
    return 35;
  }
  return 0;
}

void create() {
    ::create();
    set_property("light", 2);
    set_property("indoors", 1);
    set("long",
      "This is the race setter room.\n \n"
      "LOOK AT THE WEB PAGE!!!!!!!!!!!!!!\n"
      "http://darke.shadowlands.com\n\n"
      "Directions: 1) Read the faq... <help faq>.\n"
      "Read the newbie help...<help newbie>.\n"
      "            2) Read the race help... <help races>.\n"
      "            3) Pick the race... pick <race>.\n \n"
      " Note: type <read list> to see a list of the races.\n"
      "       type <help guilds> for a list of guilds.\n"
      "       type help <guild name> for more information on the guild.\n");
    skip_obvious();
    set_items(
      (["room" : "The nothingness from which you will be born "
	"into DarkMUD.",
	"list" : "A list of races that exist in the world of DarkeMUD."]) );
}

void init() {
    ::init();
    this_player()->setenv("SCORE", "off");
    this_player()->set("in creation", 1);
    this_player()->set_catch("off");
    add_action("read", "read");
    add_action("pick","pick");
    if (this_player()->query_exp() <= 0) {
	write("\nWelcome to DarkeMUD.   Let the CARNAGE begin!\n"
	  "Please choose a race for yourself.  Your race determines your main "
	  "genetic attributes, strength, intelligence, dexterity, constitution, "
	  "and charisma.");
	this_player()->set_rolls(0); 
    }
}

int pick(string str) {
    mapping racial_props;
    string *skill_keys, *which, *racial_keys;
    mapping borg;
    int tmp, i, j;
    string my_class, *g_dir, name;

    my_class = "child";
    if(!str) {
	return notify_fail("Please supply a race from the race list.\n");
    }
    str = lower_case(str);
    if(member_array(str, (string *)RACE_D->query_races()) == -1) {
	write("You must pick a race from the list!\nType <read list>\n");
	return 1;
    }
    printf("Ok.\nCreating your character...");
    g_dir = get_dir("/d/damned/guilds/join_rooms/*_join.c");
    i = sizeof(g_dir);
    name = (string)this_player()->query_name();
    while(i--)
	call_other("/d/damned/guilds/join_rooms/"+g_dir[i], "kick_member",
	  name);
    this_player()->remove_property("lycanthrope moon");
    this_player()->set_race(str);
    this_player()->new_body();
    this_player()->set_class(my_class);
    this_player()->init_skills(my_class);
    this_player()->add_sight_bonus((int)RACE_D->query_sight_bonus(str) -
      (int)this_player()->query_sight_bonus());
    this_player()->set_property("ambidextry", 0);
    this_player()->set_property("sp points", 0);
    racial_props = (mapping)RACE_D->query_racial_properties(str);
    if(mapp(racial_props)) {
	racial_keys = keys(racial_props);
	i = sizeof(racial_keys);
	while(i--) {
	    switch(racial_keys[i]) {
	    case "innate skills":
		if(!mapp(racial_props[racial_keys[i]])) break;
		skill_keys = keys(racial_props[racial_keys[i]]);
		j = sizeof(skill_keys);
		while(j--) {
		    this_player()->set_skill(skill_keys[j],
		      racial_props["innate skills"][skill_keys[j]]);
		}
		break;
	    case "innate spells":
		if(!mapp(racial_props[racial_keys[i]])) break;
		skill_keys = keys(racial_props[racial_keys[i]]);
		j = sizeof(skill_keys);
		while(j--) {
		    this_player()->set_spell_level(skill_keys[j],
		      racial_props["innate spells"]
		      [skill_keys[j]]);
		}
		break;
	    default:
		this_player()->set_property(racial_keys[i],
		  racial_props[racial_keys[i]]);
	    }
	}
    }
    this_player()->setenv("TITLE","Novice $N the " + capitalize(str));
    do_rolls();
    return 1;
}

void do_rolls() {
  write("Now you will assign your stats.\n"
  "DarkeMUD has a point-based stat assignment system.  Basically, "
  "you start out with a 50 in each stat and 250 points to spend.  "
  "Stats get more costly as the stat increases, ie, getting from 50 "
  "to 51 in a stat costs less than getting from 90 to 91.  You may also "
  "reduce any of your stats to as low as 35 in order to obtain extra "
  "points.  You will be provided with a table of stat costs.\n");
  printf("Press [enter] to continue: ");
  input_to("press_enter", 0, ({ 0, 0, 0, 0, 0, 0 }), 250);
  return;
}

void assign_point(string str, int *points, int pts_left) {
  int idx, i, max;
  
  if(str && lower_case(str) != "q") {
    str = lower_case(str);
    idx = member_array(str, STATS, 1);
    if(idx < 0) {
      write("'"+str+"' is not one of the available stats.\n");
      printf("Press [enter] to continue: ");
      input_to("press_enter", 0, points, pts_left);
      return;
    }
    if((int)this_player()->query("pt choice") < 0 &&
      (points[idx] + (int)this_player()->query("pt choice")) < -15) {
      write("You may only reduce a stat to 35.  No lower.");
      this_player()->set("pt choice", 0);
      printf("Press [enter] to continue: ");
      input_to("press_enter", 0, points, pts_left);
      return;
    }
    pts_left -= (int)this_player()->query("pt choice");
    points[idx] += (int)this_player()->query("pt choice");
    this_player()->set("pt choice", 0);
  }
  else if(str && lower_case(str) == "q") {
    write("Are you sure you want to quit?");
    if(pts_left > 0)
      write(sprintf("You have %d points left.", pts_left));
    printf("(yes or no): ");
    input_to("yes_or_no", 0, points, pts_left);
    return;
  }
  printf(CLS);
  write(sprintf("%|70s\n%|70s\n", "Stat Assignment", sprintf("points left: %d",
    pts_left)));
  max = sizeof(tab_str);
  write(sprintf("%'-='70s", ""));
  for(i=0;i < max;i++) {
    if(i < sizeof(STATS))
      write(sprintf("  %-18s     %-13s %3d %-+2d (%d points)",
        tab_str[i], STATS[i]+":", pt_to_stat(points[i]),
        (int)RACE_D->query_stat_adjustment(STATS[i][0..2],
          (string)this_player()->query("race")),
        points[i]));
    else
      write("  "+tab_str[i]);
  }
  write(sprintf("%'-='70s", ""));
  write("\n"+
      "Choose an amount of points you wish to spend on a stat.  "
      "Type only the number.  You will be prompted for the stat.  "
      "See the above table for the cost per stat point.  You MAY type in "
      "a negative number and reduce a stat to as low as 35.");
  printf("\nEnter a point amount ('q' to quit): ");
  input_to("pick_stat", 0, points, pts_left);
  return;
}

void yes_or_no(string str, int *points, int pts_left) {
  int i;
  int dev_tot;
  string *hands;
  
  if(str) str = lower_case(str);
  if(!str || (str != "yes" && str != "no")) {
    printf("Please enter 'yes' or 'no': ");
    input_to("yes_or_no", 0, points, pts_left);
    return;
  }
  if(str == "no") {
    assign_point(0, points, pts_left);
    return;
  }
  write("\n Finished!");
	this_player()->set_skill("attack",5);
	this_player()->set_skill("trade lore", 5);
	this_player()->set_skill("dodge", 0);
	this_player()->set_skill("parry", 0);
	this_player()->set_skill("melee",0);
	hands = (string *)this_player()->query_wielding_limbs();
	this_player()->set_property("handedness", hands[random(sizeof(hands))]);
	if(!this_player()->query_property("ambidextry"))
	    write("IMPORTANT:  You favor your "+(string)this_player()->
	      query_property("handedness") + ".  Wield weapons there\n"+
	      "when possible.");
	this_player()->set_lang_prof("common",5+(int)this_player()->
	  query_stats("intelligence")/20);
	i=sizeof(STATS);
	dev_tot=0;
	this_player()->set_property("dev points",0);
	while(i--) {
	  this_player()->set_stats(STATS[i],
	    pt_to_stat(points[i]) +
	    (int)RACE_D->query_stat_adjustment(STATS[i][0..2],
              (string)this_player()->query_race()));
	  if(STATS[i] == "charisma") continue;
	  switch((int)this_player()->query_stats(STATS[i])) {
    case 1..15:
      dev_tot += 2;
      break;
    case 16..25:
      dev_tot += 3;
      break;
    case 26..40:
      dev_tot += 5;
      break;
    case 41..60:
      dev_tot += 7;
      break;
    case 61..75:
      dev_tot += 9;
      break;
    case 76..90:
      dev_tot += 12;
      break;
    case 91..100:
      dev_tot += 15;
      break;
    case 101..105:
      dev_tot += 18;
      break;
    case 106..110:
      dev_tot += 20;
      break;
    case 111..2000:
      dev_tot += 23;
      break;
    default:
      tell_object(this_player(),"There is an ERROR in your stats.\n"+
      "Tell an Arch IMMEDIATELY.\n");
    }
  }
  dev_tot += (dev_tot * (40 +(int)this_player()->query_property("xp mod")))
    / 250;
  if(dev_tot < 42) 
      message("info", "Your stats suck.  If you would like to be deleted, "+
        "ask Drizzt or Diewarzau.", this_player());
  this_player()->set_property("dev points",dev_tot);
  this_player()->set_property("dev point base",dev_tot);
  this_player()->set_max_hp(4 * ((int)this_player()->query_stats("constitution") + 20) / 5);
  this_player()->augment_body((int)this_player()->query_stats("constitution"));
  this_player()->set_max_mp(4 * ((int)this_player()->query_stats("intelligence") + 20) / 5);
  this_player()->set_property("base mp regen", 3);
  this_player()->set_property("base hp regen", 3);
  set_ansi();
  this_player()->set("in creation", 0);
  return ;
}

void press_enter(string null, int *points, int pts_left) {
  assign_point(0, points, pts_left);
  return;
}

void pick_stat(string str, int *points, int pts_left) {
  int pts;
  
  if(str && lower_case(str) == "q") {
    assign_point("q", points, pts_left);
    return;
  }
  if(!str || !sscanf(str, "%d", pts)) {
    printf("\nPlease enter a number ('q' to quit): ");
    input_to("pick_stat", 0, points, pts_left);
    return;
  }
  if(pts > pts_left) {
    write(sprintf("You only have %d points left.", pts_left));
    printf("Press [enter] to continue: ");
    input_to("press_enter", 0, points, pts_left);
    return;
  }
  this_player()->set("pt choice", pts);
  printf("\nOk.  To which stat do you want to assign %d points?\n(first 3 letters): ",
    pts);
  input_to("assign_point", 0, points, pts_left);
  return;
}


void set_ansi() {
    this_player()->setenv("TERM", "ansi");
    this_player()->reset_terminal();
    this_player()->reset_max_exp();
    write("\nOne more thing...\n%^RED%^Is this line red (y or n)?%^RESET%^");
    input_to("set_ansi_two");
}

void set_ansi_two(string str) {
  string pass;
  
    str = arrange_string(lower_case(str), 1);
    if(str == "n") {
	write("Ok.  Terminal set to \"unknown.\"  See 'help setenv' for more info.");
	this_player()->setenv("TERM","unknown");
	this_player()->reset_terminal();
	this_player()->move(ROOM_START);
       if(wizardp(this_player()) || this_player()->query_property("reincarnate")) {
          write("You are done.");
          return;
        }
        write(
          "\nTo prevent multi-playing, a random password will be generated "
          "and mailed to you.  If you have supplied a valid email address, "
          "it should arrive almost immediately, barring net troubles.  If you "
          "do not have an email address, talk to us.  Use the guest account.  "
          "The password (surprise) is 'guest'.\n");
        pass = random_password(5+random(4));
        seteuid(UID_ROOT);
        this_player()->set_password(crypt(pass, 0));
        seteuid(UID_LOG);
        log_file("auto_pass", sprintf("%s: password set to '%s'.",
          (string)this_player()->query_name(), pass)+"\n");
        seteuid(getuid());
        delayed_call("mail_pass", 4, (string)this_player()->query_name(),
          (string)this_player()->query_email(), pass);
        seteuid(UID_FORCE);
        this_player()->force_me("quit");
        seteuid(getuid());
	return;
    }
    else if(str == "y") {
	write("Terminal set to ansi.");
	this_player()->move(ROOM_START);
        if(wizardp(this_player()) || this_player()->query_property("reincarnate")) {
          write("You are done.");
          return;
        }
        write(
          "\nTo prevent multi-playing, a random password will be generated "
          "and mailed to you.  If you have supplied a valid email address, "
          "it should arrive almost immediately, barring net troubles.  If you "
          "do not have an email address, talk to us.  Use the guest account.  "
          "The password (surprise) is 'guest'.\n");
        pass = random_password(5+random(4));
        seteuid(UID_ROOT);
        this_player()->set_password(crypt(pass, 0));
        seteuid(UID_LOG);
        log_file("auto_pass", sprintf("%s: password set to '%s'.",
          (string)this_player()->query_name(), pass)+"\n");
        seteuid(getuid());
        delayed_call("mail_pass", 4, (string)this_player()->query_name(),
          (string)this_player()->query_email(), pass);
        seteuid(UID_FORCE);
        this_player()->force_me("quit");
        seteuid(getuid());
	return;
    }
    else {
	write("Answer y or n");
	input_to("set_ansi_two");
	return;
    }
}

void mail_pass(string pname, string email, string pass) {
  external_start(1, sprintf("%s %s %s", pname, pass, email));
  return;
}

void read_cb(int sock, string mesg) {
  seteuid(UID_LOG);
  log_file("mail_pass", "Message from mailer at "+ctime(time())+"\n"+
	mesg+"\n");
  seteuid(getuid());
}

void write_cb(int sock) {
  return;
}

void close_cb(int sock) {
  return;
}

int read(string str) {
    string *res;
    int i, j, tmp;
    if(!str) {
	notify_fail("What do you want to read? A list?\n");
	return 0;
    }
    if(str != "list") {
	notify_fail("That is not here to be read.\n");
	return 0;
    }
    write("These are the following races available in our reality:");
    write("-----------------------------------------------------------");
    message("Ninfo", format_page((string *)RACE_D->query_races(), 4),
      this_player());
    write("----------------------------------------------------------");
    write("pick <race> will forever make you one of these races");
    write("Type help <race> for more information.");
    return 1;
}
