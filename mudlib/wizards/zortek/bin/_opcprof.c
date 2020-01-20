// UPDATED by Shem....who knows why it was wrong
#include <std.h>
#include <dirs.h>

inherit DAEMON;

int
cmd_opcprof(string arg)
{
   if(!archp(previous_object())) return 0;
	opcprof(DIR_LOGS + "/dumps/opcprof");
	return 1;
}

int help() {
  write( @TEXT
Syntax: <opcprof>

Puts a list of efuns and eoperators in /log/dumps/opcprof.

See also: fdinfo, netstat, mstatus, cache, callouts, dumpallobj.
TEXT
  );
  return 1;
}
