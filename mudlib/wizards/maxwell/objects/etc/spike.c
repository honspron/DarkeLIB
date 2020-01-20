//    Maxwell's Underground Mudlib 
//          Steel Column of Axe of Dulith
#include "/adm/include/std.h"

inherit OBJECT;
 
void create() {
  ::create();
    set_name("skull");
    set_id( ({ "bleached skull","skull" }) );
   set_short("a bleached skull impaled on a rusty spike" );
    set_long("The bleached skull is obviously part of the remains of an "
"unlucky adventurer. Engraved along the top of the skull is\n\n"
"   'Welcome to the Under'Drin Mines. The mines are currently\n"
"    closed to all but high-mortal play testers as I do a final\n"
"    check of all code within the zone. I expect the mines to be \n"
"    open to all adventurers shortly.\n\n"
"           Maxwell the Lord of Under'Drin Mines'\n");
    set_weight(10);
    set_value(0);
}
int move(object dest) { 
    if( living( this_player() ) ){
       if( (this_player()->query_name()) == "maxwell"){
         write("Move allowed cause your Max");
         ::move(dest);
         return;
       }
       else {
        write("The spike if firmly driven into the topsoil.");
        return 1;
       }
    }
    else {
      ::move(dest);
    }
}

