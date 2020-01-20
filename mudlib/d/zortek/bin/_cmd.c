//	--Command that takes pre-formatted cmds offline/online
//	--Purdy @ TrekVerse
//	--Aug. 22, 1994

#include <std.h>
#include <daemons.h>
#include <security.h>

#define SYNTAX	"COMPUTER: Proper Syntax is: cmd [on|off] [command]\n"
#define UPD_CMD		"/bin/system/_update.c"

inherit DAEMON;

int get_directories( string str );
int help();

int cmd_cmd( string arg )
{
   string flag, com;
   string filename, file, newfile;
   string *path, *foo;
   int i;

   if(!arg) { notify_fail( SYNTAX ); return 0; }

//	--Put in security level here

   seteuid( UID_SYSTEM );

   if(sscanf( arg, "%s %s", flag, com ) != 2) {
    notify_fail( SYNTAX );
    return 0;
   }

   if( (flag != "on") && (flag != "off") ) {
    notify_fail( SYNTAX );
    return 0;
   }

   path = get_dir( "/bin/" );
   foo = ({});
   for(i=0;i<sizeof(path);i++) {
    foo += ({ "/bin/"+path[i] });
   }
   foo = filter_array( foo, "get_directories", this_object() );
   filename = (string)CMD_D->find_cmd( com, foo );

   if(filename == "NONE") {
    notify_fail("COMPUTER: That command does not exist!\n");
    return 0;
   }

//	--Ok, so now we have the file.  One tweak to add is security...
//	We don't want coders turning off admin cmds, so we need to see
//	if the file is in /bin/power or /bin/adm and if see, then query
//	their level and see if they have rights to do that.
//	--But I'll leave that alone for now...;)

//	--So now I need to see if the file is formatted so that it can
//	be turned off and on.

   filename += ".c";
   file = read_file(filename);

   if(flag == "off") {
    newfile = replace_string( file, "#undef PROB", "#define PROB" );
    if(newfile == file) {
     notify_fail("COMPUTER: Either that command has already been turned off or it is not\nformatted to be turned off.\n");
     return 0;
    }
    printf("COMPUTER: %s has now been taken offline.\n",
     capitalize(com));
    rm(filename);
    write_file( filename, newfile );
    call_other( UPD_CMD, "do_update", filename );
    return 1;
   }

   if(flag == "on") {
    newfile = replace_string( file, "#define PROB", "#undef PROB" );
    if(newfile == file) {
     notify_fail("COMPUTER: Either that command has already been turned on or it is not\nformatted to be turned on.\n");
     return 0;
    }
    printf("COMPUTER: %s has now been brought back online.\n",
     capitalize(com));
    rm(filename);
    write_file( filename, newfile );
    call_other( UPD_CMD, "do_update", filename );
    return 1;
   }
}

int get_directories( string str )
{
   if(file_size(str) == -2) return 1;
   return 0;
}

int help() {
   write(@EndWrite
Syntax: cmd <on|off> <command>
Example: cmd off score

This command takes a command offline so while you're making bug fixes, etc,
it won't inhibit players.  It works with a #define PROB and #undef PROB in
the source code.  Commands that can be turned off/on should have an #ifdef PROB
return 0; within the code.  Look at /bin/ship/_tacstat.c for an example of
how this is used.

This command is restricted to Coders+.
EndWrite
   );
return 1;
}
