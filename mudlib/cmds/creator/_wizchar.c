/*

 * command to register wiz characters.

 *

 */



#include <daemons.h>



int cmd_wizchar(string str) {

  string type, pname;

  int tnum;

  

  seteuid(getuid());

  if(sscanf(str, "%s as %s", pname, type) != 2)

    return notify_fail("See 'help wizchar' for syntax.\n");

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

  if(!WIZCHAR_D->is_registered((string)this_player()->query_name()))

    WIZCHAR_D->register((string)this_player()->query_name(), 1,

      (string)this_player()->query_name());

  if(WIZCHAR_D->is_registered(pname)) {

    write("That player is already registered.");

    return 1;

  }

  WIZCHAR_D->register(pname, tnum, (string)this_player()->query_name());

  write("Player registered.");

  return 1;

}



void help() {

  message("help",

  "Registers a wizard test character or player with the database.  "

  "All wizards, with the exception of arches, MUST register any test characters "

  "or players, or they risk deletion.  Arches are strongly encouraged to register "

  "as well.\n\n"

  "Syntax (player):   wizchar <name> as player\n"

  "             Ex:   wizchar bignatz as player\n"

  "Syntax (testchar): wizchar <name> as testchar\n"

  "               Ex: wizchar diewarzaui as testchar\n",

  this_player());

}



