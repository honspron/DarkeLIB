//	/bin/dev/_sponsor.c

//	from the Nightmare mudlib

//	a command to allow mentors to sponsor new wizards

//	created by Descartes of Borg 31 january 1993



#include <std.h>

#include <security.h>

#define CHANGE_GROUPS ({ "wizard" })





inherit DAEMON;



void rewrite_groups_db(string name);



int cmd_sponsor(string str) {

    string file, pos, nom;

    string *lines;

    int i, lev ;

    object who, ob;



    if(!str) {

	notify_fail("Sponsor whom?\n");

	return 0;

    }

   sscanf(str, "%s", nom); 

   if(!(ob = find_player(nom = lower_case(nom))))

      return notify_fail(sprintf("Cannot find %s anywhere.\n",capitalize(nom)));

    who = find_living(str);

    lev = 100;



    if((string)who->query_position() != "player") {

	notify_fail(capitalize(str)+" is not a player!\n");

	return 0;

    }

    str = "wizard";

//if(!archp(this_player()) && !mentorp(this_player()) && !elderp(this_player()) {

  if(!archp(this_player()) && (string)!this_player()->query_position() != "elder" && (string)!this_player()->query_position() != "mentor") {

        notify_fail("You are not allowed to sponsor anyone!\n");

	return 0;

    }

    seteuid(UID_LOG);

    log_file("sponsor", sprintf("%s sponsored %s on %s.\n", (string)previous_object()->query_name(), nom, ctime(time())));

    log_file("xmote", sprintf("%s went to wizard thanks to "

			      "%s on %s.\n", nom, (string)previous_object()->query_name(),

			      ctime(time())));

    seteuid(UID_ADVANCE);

    ob->set_position(str);

    ob->set_level(lev);

    seteuid(getuid());

    message("info", sprintf("%s is now position wizard", capitalize(nom),

			    str), this_player());

    message("info", sprintf("You have been xmoted to %s", str), ob);

    seteuid(UID_ROOT);

    mkdir("/wizards/"+lower_case(nom));

    write_file(user_path(nom)+"workroom.c", read_file("/std/obj/workroom.c"));

    seteuid(getuid());

    message("info", sprintf("You are now an immortal!\nYour home "

      "directory is %s.", user_path(nom)), who);

    message("info", sprintf("%s is now a coding slave of DarkeMUD!", capitalize(nom)),

      users(), ({ who }));

    return 1;

}



void help() {

    write("Syntax: <sponsor [player]>\n\n"+

	"This cmd makes a player a wizard(makes their dir and makes them "+

        "a workroom too).  If you sponsor a wiz he is your bagage!"+

        "  Bagage meaning you handle his problems and show him the ropes"+

        "  If he screws up it is on your head!\n");

}





void rewrite_groups_db(string name) {

    string *groups_db;

    string old_euid, pos, group;

    int i, start;



    pos = "wizard";

    name = lower_case(name);

    old_euid = geteuid(this_object());

    seteuid(UID_ADVANCE);

    groups_db = explode(read_file("/adm/db/groups.db"),"\n");

    start = member_array("("+pos+")",groups_db,1);

    if(start < 0) {

        seteuid(old_euid);

        return;

    }

    if(member_array(name,explode(groups_db[start]," ")) < 0)

        groups_db[start] += " "+name;

    rm("/adm/db/groups.db");

    for(i=0;i<sizeof(groups_db);i++) {

        if(groups_db[i][0..0] == "#") continue;

        else {

            if(sscanf(groups_db[i],"(%s)%*s", group) &&

                group != pos && member_array(group,CHANGE_GROUPS) > -1)

                groups_db[i] = replace_string(groups_db[i]," "+name,"");

        }

    }

    for(i=0;i<sizeof(groups_db);i++) {

        write_file("/adm/db/groups.db",groups_db[i]+"\n");

    }

    master()->load_groups();

    seteuid(old_euid);

    return;

}

