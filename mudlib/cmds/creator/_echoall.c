//      /bin/dev/_echoall.c

//      from the Nightmare Mudlib

//      echos to everyone on the mud

//      created by ????



#include <std.h>

#include <security.h>



inherit DAEMON;



int cmd_echoall(string str) {

    if(!str) {

        notify_fail("Echoall what?\n");

        return 0;

    }

    message("shout", str, users());

    seteuid(UID_LOG);

    log_file("shouts", geteuid(previous_object())+" (echoall): "+str+"\n");

    seteuid(getuid());

    return 1;

}



void help() {

    message("help",

      "Syntax: <echoall [message]>\n\n"

      "Sends the message to all users in the game.  Abuse of this "

      "power can result in serious action from law.", this_player()

    );

}

