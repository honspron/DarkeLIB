#include <std.h>



inherit DAEMON;



int

cmd_malloc(string arg)

{

	this_player()->more(explode(malloc_status(), "\n"));

	return 1;

}



int help()

{

  write( @EndText

Syntax: malloc

Effect: Lists memory usage statistics

        Output will depend on memory management package specified in options.h

        when the driver is compiled.

See man: malloc_status

EndText

  );

  return 1;

}

