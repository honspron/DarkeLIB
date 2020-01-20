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
}

