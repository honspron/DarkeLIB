/*
  A command to challenge a guildmaster!

  Diewarzau 7/5/96
  DarkeLIB 1.0
*/

#define ARENA "/std/diewarzau/rooms/gm_arena"
#include <daemons.h>

int cmd_challenge(string str) {
  string jr, tmp;
  object gm;

    write("The challenge command is bugged, please don't use it.\nIf you need to change guildmasters speak to an arch.\nThanks,\n\tThrace.");
    return 1;
  seteuid(getuid());
  if(lower_case(str) != "guild master") return 0;
  if(!this_player()->query_class() ||
     (string)this_player()->query_class() == "child") {
    write("Sorry, you must be in a guild to challenge the master.");
    return 1;
  }
  if(wizardp(this_player())) {
    write("Wizards cannot challenge.");
    return 1;
  }
  if(this_player()->query_guild() && 
    (string)this_player()->query_guild() !=
    "none" && (string)this_player()->query_name() ==
    (string)CLAN_D->clan_leader((string)this_player()->query_guild())) {
    write("You may not issue a challenge if you own a clan.");
    return 1;
  }
  jr = sprintf("/d/damned/guilds/join_rooms/%s_join",
	       (string)this_player()->query_class());
  if(!file_exists(jr+".c")) {
    write("BUG....could not find your guild.");
    return 1;
  }
  tmp = (string)jr->query_master();
  if(!tmp) {
    write("Your guild does not have a player guild master yet.\n"+
	  "You must defeat the NPC guild master in the joining room if "
	  "you wish to become guild master.");
    return 1;
  }
  if(!(gm = find_player(tmp))) {
    write("The guildmaster must be on the mud for you to challenge him.");
    return 1;
  }
  if(ARENA->query_cip()) {
    write("The guildmaster arena is in use.");
    return 1;
  }
  "/daemon/chat"->send_chat("darke", "DemiUrge", 
    capitalize(this_player()->query_true_name())+
    " has challenged "+
    capitalize(this_player()->query_true_name())+
    ", guildmaster of the "+pluralize(capitalize((string)gm->query_class()))+"!");
  "/daemon/chat"->send_chat("darke", "DemiUrge", 
    "Another member of the "+capitalize((string)gm->query_class())+
    " guild is needed to <second> the challenge.");
    
  ARENA->set_cip(0);
  ARENA->set_cip(1);
  ARENA->set_gm(gm);
  ARENA->set_chal(this_player());
  new("/std/diewarzau/obj/misc/gm_soul")->move(gm);
  message("info", "If you quit or are net dead when and if the challenge is "
	  "seconded, you will automatically lose the challenge.",
	  gm);
  new("/std/diewarzau/obj/misc/chal_soul")->move(this_player());
  message("info", "If you quit or are net dead at the time that the "
	  "challenge is seconded, the challenge will be negated.",
	  this_player());
  delayed_call("time_out", 30, gm, this_player());
  return 1;
}

void time_out(object gm, object chal) {
  object ob;

  "/daemon/chat"->send_chat("darke", "DemiUrge", 
    "The challenge has not been seconded, and therefore expires!");
  ARENA->set_cip(0);
  ARENA->set_gm(0);
  ARENA->set_chal(0);
  if(gm && (ob=present("challenge soul", gm))) ob->remove();
  if(chal && (ob=present("challenge soul", chal))) ob->remove();
  return;
}

void remove_to_call() {
  remove_delayed_call("time_out");
  return;
}

int help() {
  message("help", 
	  "This command is used to challenge the authority of your "
	  "guildmaster.  You MUST have a player guild master to "
	  "do this.  You are transported to an arena where you "
	  "will fight to the death.  If the guild master wins, "
	  "the challenger will die as normal.  If the challenger "
	  "wins, the guild master will suffer no death penalty, but "
	  "will lose his/her guild mastership.\n"
	  "NOTE: You must have another person in your guild "
	  "second the challenge once it is made.  A guild master "
	  "may second his/her own challenge.\n"
	  "\n"
	  "Syntax: 'challenge guild master'", this_player());
  return 1;
}











