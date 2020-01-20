//       Maxwell's Underground Mudlib 
//             Generic help Object
#include "/adm/include/std.h"

inherit OBJECT;

void init() {
   add_action("help","help");
} 
void create() {
  ::create();
    set_name("book");
    set_id( ({ "book","help manual","manual" }) );
   set_short("a sturdy leather book" );
   set_long("This is a book about guildmaster commands. Just type "
   "'help guildmaster' for the guildmaster help file.");
    set_weight(100);
    set_value(0);
}
int dis(string fun){
   remove();
}
void help(string str){
 if(str == "guildmaster"){
     write(
"allow <player>\n"+
"\tAllows <player> to join your guild.\n"+
 // "\ndismiss <player>\n"+
//"\tKicks <player> out of your guild.  The player does NOT have to be on to do this.\n"+
"\nlist members\n"+
"\tGet a complete list of guild membership.\n"+
"\nallowtrain <player>\n"+
"\tAllows <player> to enter your skill and/or spell training room ONCE to train.  "+
"<player> does not need to be a member of your guild to do this.\n"+
"YOU MUST pay a donation of "+
to_int(2000.0*currency_rate("platinum"))+
" platinum per level of the player to your patron deity to do this.\n"+
"\nhelp guildmaster\n"+
"\tThis help.\n" +
"\nsetpriv <privilege> for <player>\n"+
"\tGives adds or removes <privilege> from <player>.\n"+
"Current privileges:\n"+
"'treasury restrict'  - Bars the player from entering the treasury\n"
"'allow join' - other players in the guild may allow players to join "
"by typing 'allow <player>' IN THE JOIN ROOM of the guild.");
 }
 if(str == "castle"){
write( "Castle commands:\n"
"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n"
"castle list......................Lists all castle 'things' available\n"
"castle exit <direction> <room>...Adds an exit from the current room\n"
"Ex: castle exit north 4          <room> in the direction <direction>\n"
"   ^ adds an exit to room 4      must be north, south, east, west, up,\n"
"                                 or down.\n"
"castle door <door-num> <dir>.....Adds a door to the direction <dir>.\n"
"Ex: castle door 4 north\n"
"\n"
"castle remove door <dir>.........Removes the door on the <dir> exit\n"
"Ex: castle remove door north     and puts it back in your inventory.\n"
"castle remove exit <dir>.........Removes the exit <dir>\n"
"castle feature <feature>.........Adds <feature> to the current room.\n" 

"Ex: castle feature no summon     Some feartues include, healing room, \n"
"                                 no summon, no teleport, and no scry.\n"
"castle remove feature <feature>..Removes <feature> from the current\n"
"                                 room and puts it in your inventory.\n"
"castle features..................Lists all featurs in the current\n"
"                                 room.\n"
"castle goto <num>................Teleports you to room number <num>.\n"
"castle where.....................Tells you where anyone in your castle\n"
"                                 in by room number.\n"
"castle short <desc>..............Changes the short dec of the room\n"
"                                 to <desc> (40 char. max)\n"
"castle long......................Opens and editor to put in the\n"
"                                 long description...10 lines max.\n"
"castle light <level>.............Changes the light in the room to\n"
"                                 <level>...may be either 'dark',\n"
"                                 'light', or 'bright'.\n");
  return 1;
}


}

