//	/bin/user/_background.c
//	from the Darkemud mudlib
//	created by Shadowraith the Damned 02 october 1996

#include <std.h>
#include <security.h>
#include <daemons.h>

inherit DAEMON;

int cmd_background(string text);
int help();


int
cmd_background(string text)
{
    string str, new_text;
    string file,who,*whol;
    string *allbg;
    object ob;
    int i,j;

    ob = this_player();
    if( !text )
    {
       help();
       return 1;
    }
    text = lower_case(text);
    file = "/data/backgrounds/"+ text +".b";
    if( (file_size(file) > 0) &&
            (text != "set") &&
            (text != "delete") &&
            (text != "list") )
    {
       ob->more(file);
       return 1;
    }
    else if(text == "list") {
      allbg=get_dir("/data/backgrounds/");
      j=sizeof(allbg);
      whol = ({""});
      for(i=0; i < j; i++) {
         sscanf(allbg[i],"%s.b",who);
         whol +=({"%^BLUE%^"+capitalize(who)});
      }
      message("info","The Following Characters have backgrounds:",this_player());
      this_player()->more(whol);
      return 1;
    }
    else if(text == "set")
    {
       file="/data/backgrounds/"+ ob->query_name() + ".b";
       ob->edit(file);
       message("info","You have updated your background.\n",ob);
       return 1;
    }
    else if(text == "delete")
    {
       file="/data/backgrounds/"+ ob->query_name() + ".b";
       if(file_size(file) > 0) rm(file);
       message("info", "Your background file has been deleted.\n",ob);
       return 1;
    }
    else
       return notify_fail (capitalize(text)+ " has not created a character background.\n");
}

int
help()
{
	write(
	"Syntax: <background [name/set/delete/list]>\n"+
	"\n"+
	"When name is given, returns tha background (if any) of that.\n"+
	"character.  When set is specified, it opens an editor to write/edit "+
        "the background history of the character. if delete is specified, \n"+
        "it remove the character's background file.  If list is specified\n"+
        " it will list all character's with backgrounds.\n"+
	"\nSee also: biography, score, and roleplay.\n");
	return 1;
}
