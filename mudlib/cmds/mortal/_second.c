/*
  Command for sponsoring GM chllenges

  Diewarzau 7/5/96
  DarkeLIB 1.0
*/

#define ARENA "/std/diewarzau/rooms/gm_arena"

int cmd_second(string str) {
  object chal;

  if(!str) return 0;
  if(wizardp(this_player())) {
    write("Wizards may not second challenges.");
    return 1;
  }
  if(!ARENA->query_cip()) {
    write("There is no challenge for you to sponsor.");
    return 1;
  }
  chal = (object)ARENA->query_chal();
  if(!chal) {
    write("Cannot find challenger...this is a bug.");
    return 1;
  }
  if((string)chal->query_class() != (string)this_player()->query_class()) {
    write("You must be of the same guild as the challenger to second.");
    return 1;
  }
  if(chal == this_player()) {
    write("Uh, no...");
    return 1;
  }
  "/daemon/chat"->send_chat("darke","DemiUrge",
    "The challenge has been seconded by "+
    capitalize((string)this_player()->query_true_name())+"!");
  call_other("/cmds/mortal/_challenge", "remove_to_call");
  ARENA->sponsor(this_player());
  return 1;
}

int help() {
  message("help",
	  "This command is used to second a guild master challenge.  "
	  "You must be in the same guild as the challenger.\n"
	  "A guild master MAY sponsor a challenge against himsel/herself!\n"
	  "\n"
          "Syntax: second <who>", this_player());
  return 1;
}

