//	/cmds/creator/_whereis.c

//	Tells you the filename of the environement of a player

//	by Kalinsh@Nightmare 17 Jan 94



#include <std.h>



inherit DAEMON;



int cmd_whereis(string drow) {

    object ob;



    if(!drow)

        return notify_fail("Whereis who?\n");

    if(!ob=find_player(drow))

        return notify_fail("I can't seem to locate them.\n");

    message("info", sprintf("You find %s in :", 

      ob->query_cap_name()), this_player());

    message("info", sprintf("%s.c", file_name(environment(ob))),

      this_player());

    return 1;

}



void help() {

    message("help", "Usage : whereis [player]\n\nTells you the "

      "filename of the room that [player] is in.", this_player());

}

