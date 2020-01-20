//Zortek 960321 Created as a temporary measure to dest corpses. 
 
#include <std.h>
inherit DAEMON;
 
int cmd_reaper() {
 
string *ob;
int i, foo;
  foo = 0;
  ob = children("/std/obj/mon_corpse");
  for(i=0;i<sizeof(ob);i++) {
     write("Corpse:  ["+ob[i]->query_name()+"] Buried.");
     ob[i]->preserve_me(0);
     ob[i]->remove();
     foo++;
  }
  write("+------------------------------+\nCorpses buried:  "+foo);
//message("info", "%^RED%^An Undertaker just buried "+foo+" corpses.%^RESET%^", users());
  return 1;
}		
 
void help(){
     write(@HELP
Syntax: reaper
 
Buries all active corpses in the game.  Effectively,
this creates an array of corpse objects and then removes
each of them keeping a tally.
HELP
);
}
