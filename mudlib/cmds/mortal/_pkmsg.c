#include <std.h>
#include <ansi.h>

inherit DAEMON;      
int cmd_pkmsg(string str) {
    int level;
    string name, title, pre, gen, message;
    level = (int)this_player()->query_level();
    title = (string)this_player()->query_title();
    name = (string)this_player()->query_cap_name();
    gen = (string)this_player()->query_gender();
    message = this_player()->query_property("pkmsg");
    if(!str) {
        notify_fail("PK message is currently: "+message+"\n");
        return 0;
    }
    if (strsrch(str, "ME")==-1){
       notify_fail("Your PK message must contain ME!\n");
         return 0; 
    }
    if (strsrch(str, "TARGET")==-1){
       notify_fail("Your PK message must contain TARGET!\n");
         return 0; 
    }
    if(level < 12)  {
         notify_fail("You must be level 12 to set your PK message!\n");
         return 0;      
         }
        this_player()->set_property("pkmsg", str);
        write("Your PK message is now: "+str+"\n");
    return 1;
}

void help() {
    write("Syntax: <pkmsg [new pkmsg]>\n\n"+
        "Changes your PK message which shows up when you PK people.\n"+
        "This message must contain 'ME' which will be replaced with your name\n"+
        "and 'TARGET' which will be replaced by the targets name");
}
