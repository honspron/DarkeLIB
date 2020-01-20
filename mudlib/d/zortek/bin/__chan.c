 
//_lines.c
//A utility to help wizards keep track of what lines they're
//on, and to them turn all off and on with one command.
//by Gregon@nightmare
//
//Zortek 960321 Modifed the display to be easier to read
//at a glance. 
 
#include <std.h>
inherit DAEMON;
 
int cmd_lines(string str) {
 
string *ob, guild;
int i, foo;
 
ob = (string *)this_player()->query_channels();
  if(!str) {
  write("%^BLUE%^+--------------------------------------------------------+%^RESET%^");
     for(i=0; i<sizeof(ob); i++) {
       if(this_player()->query_blocked(ob[i]))
         printf("[ ]  %-12s    ",ob[i]);
       else printf("[X]  %-12s    ",ob[i]);
       if(i%3 == 0) printf("\n");
     }
  write("%^BLUE%^+--------------------------------------------------------+");
  write("%^BLUE%^|%^RESET%^         [X] On Channel         [ ] Off Channel         %^BLUE%^|%^RESET%^");
  write("%^BLUE%^+--------------------------------------------------------+%^RESET%^");

  return 1;
}
 
  if(str=="on"){
      for(i=0; i<sizeof(ob);i++){
      if(this_player()->query_blocked(ob[i]))
        this_player()->set_blocked(ob[i]);
     }
     return 1;
}
 
  if(str=="off"){
      for(i=0; i<sizeof(ob);i++){
      if(!this_player()->query_blocked(ob[i]))
        this_player()->set_blocked(ob[i]);
     }
     return 1;
}
 
}		
 
void help(){
     write(@HELP
Syntax: lines -or- lines [on|off]
 
With no argument this command will display the status of the
lines/channels to which you have access.  With the argument
on|off it will turn all of the lines on or off.
HELP
);
}
