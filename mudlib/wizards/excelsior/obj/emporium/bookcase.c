// /wizards/excelsior/obj/emporium/bookcase

#include <std.h>

#define WHATS_HERE ({"city guide","map","device instructions","banishment letter","play"})
// strlen can be no more then 21
#define LOCATIONS ({"/wizards/excelsior/doc/city_guide","/wizards/excelsior/doc/level1_pmap","/wizards/excelsior/doc/packing","/wizards/excelsior/doc/admin_letter","/wizards/excelsior/doc/play"})
#define TITLES_PER_LINE 2
// if 4 titles are wanted per line, this should be defined as 3 etc.

inherit OBJECT;

void init() {
	::init();
	add_action("read","read");
}

void create() {
	::create();
	set_name("bookcase");
	set("id",({"bookcase","book case","case","book shelves"}));
	set("short","A book case");
	set("long","These book shelves contain books about the area, darke in "+
		"general,  and anything else amusing. To see a list of whats here "+
		"type 'read list'. When you find something you want to read, 'read "+
		"<title>.");
	set_weight(10000000);
	set_value(0);
}

int read(string str) {
	int i,n,tab_check,ind;
	if(strlen(str) >= 4 && str[0..3] == "list") {
		write("The shelves contain the following titles:");
		write("=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=");
		i = sizeof(WHATS_HERE);
		i--;
		while(i > -1) {
			if(n >= TITLES_PER_LINE) {
				n = 0;
				message("info","\n",this_player());
			}
			tab_check = 22-strlen(WHATS_HERE[i]);
			message("Ninfo",WHATS_HERE[i],this_player());
			while(tab_check>0) {
				message("Ninfo"," ",this_player());
				tab_check--;
			}
			n++;
			i--;
		}
		message("info","\n",this_player());
		return 1;
	}
	ind = member_array(str,WHATS_HERE);
	if(ind == -1) {
		notify_fail("You cannot find that title.\n");
		return 0;
	}
	write("You read the book...");
	this_player()->more(LOCATIONS[ind]);
	return 1;
}
