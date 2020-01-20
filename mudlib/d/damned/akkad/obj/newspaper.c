/* Newspaper for town crier */
/* Written by Traer for Darke Domain */
/* 3-22-99 */
#include <std.h>
inherit "/std/Object";
object who;
void init() {
   ::init();
   add_action("read", "read");
   add_action("drop", "drop");
}

void create() {
::create();
   set("id", ({"paper", "newspaper", "sentinel times"}) );
   set_name("newspaper");
   set("short", "today's current newspaper.");
   set("long", "This is totay's current edition of the Sentinal Times. All of the current events and happens can be read here as the news is reported from across the realms.");
   set_weight(10);
   set("value", 0);
}

int read(string str) {
   if(!str) {
      return 0;
   }   
   if((str != "paper") && (str != "newspaper") && (str != "sentinal times")) { 
      notify_fail("Read what?\n");
      return 0;
   }
    write("Today's Headlines!\n\n"
"Town crier created for Akkad Township by Traer - 3/22/99\n"

"Sentinal Times created by Traer - 3/22/99\n"

"More news will be added as reporters are placed in the field.\n"
         );
   return 1;
}
int drop(string str) {
   if(!str)
      return 0;
   if((str != "paper") && (str != "newspaper") && (str != "sentinal times"))
      return 0;
   write("The newspaper is caught by the wind and is swept out of sight!");
   say(this_player()->query_cap_name()+" drops a newspaper and the wind carries if off out of sight."); 
   this_object()->remove();
   return 1;
}
