//  /bin/user/_languages.c
//  written by Valodin, August 12, 1993


#include <std.h>


inherit DAEMON;

int cmd_languages(string str)
{
  string *langs;
  int i , lsz, prof, flag;

  flag = 0;
  langs = this_player()->query_all_languages();
  if((lsz = sizeof(langs)) == 0)
  {
    write("    ");
    return 1;
  }
  write("Your primary language is " + 
	capitalize((string)this_player()->query_primary_lang()) + ".");
  for(i = 0; i < lsz; i++)
  {
    prof = this_player()->query_lang_prof(langs[i]);
    switch(prof)
      {
      case 0:
	break;
      case 1:
      case 2:
      case 3:
      case 4:
	write("You are just beginning to learn " + capitalize(langs[i]) + ".");
	break;
      case 5:
      case 6:
      case 7:
	write("You are moderately skilled at " + capitalize(langs[i]) + ".");
	break;
      case 8:
      case 9:
	write("You are very skilled at " + capitalize(langs[i]) + ".");
	break;
      case 10:
	write("You are fluent in " + capitalize(langs[i]) + ".");
      }
  }
  return 1;
}

int help()
{
  message("help", "Command: languages\n"
	  "Syntax: languages\n\n"
	  "This command tells you all the languages you can speak.  If you "
	  "have problems with languages, you should visit the sage and ask "
	  "him to fix you.  If you are skilled in one of these languages you "
	  "should also visit the sage and have him fix you:\n"
	  "  elvish, giantish, orcish, artellian, mischief, sensuous,\n"
	  "  hobbitish, pseudo-speak, or gnomish", this_player());
  message("help", "\nSee also: tongues, speak, shout", this_player());
  return 1;
}
