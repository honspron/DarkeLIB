/*  /cmds/creator/_destall.c

 *  Made for DarkeMUD

 *  Created by Geldron 031096

 *  Copyright (c) 1996, DarkeMUD

 *  Do not remove this header

 */





inherit DAEMON;



int cmd_destall(string arg) {

    object *tmp;

    int i;



    if(!arg) {

	message("destall", syntax("destall FILENAME"), TP);

	return 1;

    }

seteuid(getuid(TP));

    arg = resolv_path(arg);

    if(file_size(arg) < 1) 

	arg = TP->get_path() + "/" + arg;

    if(file_size(arg) < 1)

	arg = arg + ".c";

    if(file_size(arg) < 1) {

	message("destall", arg + " doesn't exist.", TP);

	return 1;

    }

    tmp = children(arg);

    for(i = 0; i < sizeof(tmp); i++) 

	tmp[i]->remove();

    message("destall", "%^ORANGE%^D%^RED%^o%^GREEN%^n%^BLUE%^e%^RESET%^%^BOLD%^.",

      TP);

seteuid(0);

    return 1;

}



void help() {

    message("destall_help", syntax("destall FILENAME") + "\n\n"

      "Dests all of FILENAMEs.", TP);

}

