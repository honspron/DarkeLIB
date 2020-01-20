//	/cmds/adm/_autoremove.c

//	Controls the inactivity daemon which removes inactive players.

//	Can be used to change protected groups, users, and max time

//	allowed before deletion.

//	DarkeLIB 0.1

//	Diewzarzau (4/1/94)



#include <daemons.h>

#include <security.h>

#include <dirs.h>

#include <clock.h>



mapping remove_info;



int cmd_idaemon(string str) {

    string what;

    int amt;



    seteuid(getuid());

    if(!str) {

	seteuid(UID_SECURE_DAEMONSAVE);

	if(!restore_object(DIR_SECURE_DAEMONS_SAVE+"/inactivity"))

	return notify_fail("Cannot load daemon data.\n");

	seteuid(getuid());

	write("Auto remove daemon statistics:");

	write("--------------------\nProtected groups:\n"

	+"--------------------");

	if(sizeof(remove_info["positions protected"]))

	    write(format_page(remove_info["positions protected"],3));

	else

	    write("none");

	write("--------------------\nUsers Protected:\n"

	    +"--------------------");

	if(sizeof(remove_info["who protected"]))

	    write(format_page(remove_info["who protected"],3));

	else

	    write("none.");

	write("--------------------\nTime to player remove: " +

		identify(remove_info["max player time"]/MONTH)+

		" mud months.");

	write("Time to wizard remove: "+

		identify(remove_info["max wiz time"]/MONTH) +

		" mud months.");

	return 1;

    }

    if(sscanf(str,"player time %d", amt) == 1) {

	INACTIVITY_D->set_max_player_time(amt);

	write("Players now deleted after " + identify(amt) + " mud months.");

	return 1;

    }

    if(sscanf(str, "wiz time %d",amt) == 1) {

	INACTIVITY_D->set_max_wiz_time(amt);

	write("Wizards now deleted after "+identify(amt)+" mud months.");

	return 1;

    }

    if(sscanf(str,"add user %s",what) == 1) {

	INACTIVITY_D->add_protected_player(what);

	write(capitalize(what) + " will never be deleted.");

	return 1;

    }

    if(sscanf(str,"remove user %s",what) == 1) {

	amt = INACTIVITY_D->remove_protected_player(what);

	if(amt) {

	    write(capitalize(what)+ " may now be deleted again.");

	    return 1;

	}

	else

	    return notify_fail("That player is not protected.\n");

    }

    if(sscanf(str,"add position %s", what) == 1) {

	INACTIVITY_D->add_position_protected(what);

	write(capitalize(what) + "s will never be deleted.");

	return 1;

    }

    if(sscanf(str,"remove position %s",what) == 1) {

	amt = INACTIVITY_D->remove_position_protected(what);

	if(amt) {

	    write(capitalize(what)+ "s may now be deleted again.");

	    return 1;

	}

	else

	    return notify_fail("That position is not protected.\n");

    }

    return notify_fail("Invalid syntax, see help.\n");

}



void help() {

message("help",

"This command controls the operation of the user inactivity daemon.  "

"This daemon searches for inactive players and wizzes and deletes them "

"if they have been inactive for a certain amount of time.  Valid syntax "

"for this command is:\n"

"idaemon - gives all the set variables of the daemon\n"

"idaemon player time <mud months> - number of mud months before a player is "

"deleted.\n"

"idaemon wiz time <mud months> - same for wizards.\n"

"idaemon add user <who> - adds a user which may not be deleted ever.\n"

"idaemon remove user <who> - removes a protected user.\n"

"idaemon add position <pos> - add a position protected from deletion.\n"

"idaemon remove position <pos> - oppsite of above.",this_player());

}

