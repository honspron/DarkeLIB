//   Add quest points!



#include <security.h>



int cmd_addquest(string str) {

  object who;

  string name;

  int amt;

  

  if(!archp(this_player())) return 0;

  if(sscanf(str, "%d to %s", amt, name) != 2) {

    write("Syntax: addquest <amount> to <player>");

    return 1;

  }

  who = find_player(lower_case(name));

  if(!who) {

    write("Could not find: "+name);

    return 1;

  }

  seteuid(UID_ROOT);

  who->add_quest_points(amt);

  seteuid(getuid());

  write("Ok.");

  message("info", "You receive "+amt+" quest points.", who);

  return 1;

}



int help() {

  message("help",

  "This command is used to add quest points to a player.\n"+

  "Syntax: addquest <amount> to <player>", this_player());

  return 1;

}



