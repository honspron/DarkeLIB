/*  /cmds/mortal/_colour.c
 *  Made for DarkeMUD
 *  Created by Geldron 031396
 *  Copyright (c) 1996, DarkeMUD
 *  Do not remove this header
 */

#include "/wizards/geldron/pt/valid_colour.c"

inherit DAEMON;

int cmd_colour(string arg) {
    string arg1, arg2, *kcolours, *vcolours;
    int i;

    kcolours = keys((mapping)TP->query_colours());
    vcolours = values((mapping)TP->query_colours());
    if(arg == "types") {
	write("%^RED%^" + repeat_string("-=", 16) + "] %^GREEN%^Types %^RED%^[" +
	  repeat_string("=-", 16) + "%^RESET%^");
	if(kcolours && sizeof(kcolours) && vcolours && sizeof(vcolours))
	    for(i = 0; i < sizeof(kcolours); i++)
		write(vcolours[i] ? kcolours[i] + ": " + vcolours[i] :
		  kcolours[i] + ": none");
	write("%^RED%^" + repeat_string("-=", 36) + "-%^RESET%^");
	return 1;
    }
    if(!arg || sscanf(arg, "%s %s", arg1, arg2) != 2) {
	message("colour_syntax", syntax("colour TYPE|TYPES [COLOUR|none]"), TP);
	return 1;
    }
    if(!valid_colour(arg2) && arg2 != "none") {
	write("Invalid colour.  Type \"colours\" for more information.");
	return 1;
    }
    if(arg2 == "none") TP->remove_colour(arg1);
    else
	TP->set_colour(arg1, arg2);
    write("Ok.");
    return 1;
}

void help() {
    message("colour_help", syntax("colour TYPE|TYPES [COLOUR|none]") + "\n\n"
      "this command changes your colour settings.  For more "
      "information, type \"help common_types\".\n\nSee also: colour", TP);
}
