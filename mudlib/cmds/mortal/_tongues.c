#include <std.h>
#include <daemons.h>

inherit DAEMON;

string plural(string race)
{
  int rln;
  if(race[(rln = strlen(race)) - 1] == 'f')
    return (race[0..(rln - 2)] + "ves");
  return (race + "s");
}

int cmd_tongues()
{
  string *races, *langs, *report;
  int i, rln;
  races = (string *)LANG_D->all_races();
  langs = (string *)LANG_D->all_languages();
  report = ({});
  for(i = 0, rln = sizeof(races); i < rln; i++)
    report += ({ capitalize(langs[i]) + " is spoken by the " +
          capitalize(plural(races[i])) + "." });
  this_player()->more(report);
    return 1;
}

int help()
{
  message("help", "Command: tongues\n\nThis lists the languages spoken by "
          "the different races.", this_player());
  message("help", "See also: languages, speak, shout", this_player());
  return 1;
}
