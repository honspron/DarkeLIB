/*

 * command to register wiz characters.

 *

 */



#include <daemons.h>



int cmd_adwizchar(string str) {

  string type, pname, wname;

  int tnum;

  

  seteuid(getuid());

  if(sscanf(str, "%s as %s for %s", pname, type, wname) != 3) {

    wname = 0;

    if(sscanf(str, "%s as %s", pname, type) != 2)

      return notify_fail("See 'help adwizchar' for info on syntax.\n");

  }

  switch(type) {

  case "testchar":

    tnum = 3;

    break;

  case "player":

    tnum = 2;

    break;

  default:

    write("You may only register a player as a 'player' or a 'testchar'.");

    return 1;

  }

  pname = lower_case(pname);

  if(!user_exists(pname)) {

    write("The player: '"+pname+"' does not exist.");

    return 1;

  }

  if(wname) {

    wname = lower_case(wname);

    if(!user_exists(wname)) {

      write("The wizard: '"+wname+"' does not exist.");

      return 1;

    }

  } else wname = (string)this_player()->query_name();

  if(!WIZCHAR_D->is_registered(wname))

    WIZCHAR_D->register(wname, 1, wname);

  if(WIZCHAR_D->is_registered(pname)) {

    write("That player is already registered.");

    return 1;

  }

  WIZCHAR_D->register(pname, tnum, wname);

  write("Player registered for "+wname+".");

  return 1;

}



void help() {

  message("help",

  "This command functions exactly like the creator command 'wizchar', except "

  "that it may be used to register players for OTHER wizards.  Simply use the same "

  "syntax, except add 'for <whom>' afterward, where <whom> is the wizard for whom "

  "you are registering a player or testchar.  If 'for <whom>' is not supplied, this "

  "command functions EXACTLY like 'wizchar'.",

  this_player());

}



