//   Command to generate a new password for a player.

//

//   Diewarzau

//   DarkeLIB 1.0



#include <daemons.h>

#include <security.h>



int cmd_genpass(string str) {

  string pass;

  

  str = lower_case(str);

  if(!user_exists(str) || str == "guest") {

    write("No such user: '"+str+"'.");

    return 1;

  }

  seteuid(UID_ROOT);

  write("Password generated for "+str+": '"+

    (pass=(string)EMAIL_D->generate_pass(str))+"'.");

  seteuid(UID_LOG);

  log_file("change_pass", sprintf("Random password for %s: %s\n",

    str, pass));

  seteuid(getuid());

  return 1;

}



int help(){

  message("help",

  "This command is used to generate a random password for a player.  "

  "The password is generated and returned to the arch.  It is also "

  "logged in /log/change_pass.\n"

  "\n"

  "Syntax: genpass <player>\n",

  this_player());

  return 1;

}

