//    Maxwell's Underground Mudlib 
//          Steel Column of Axe of Dulith
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("skull");
    set_id( ({ "bleached skull","skull" }) );
   set_short("a bleached skull impaled on a rusty spike" );
    set_long("The bleached skull is obviously part of the remains of an "
"unlucky adventurer. Engraved along the top of the skull is\n\n"
"   'Welcome to the Under'Drin Mines. The mine is offically open\n"
"    to all would dare to enter. Mail me or use bug/typo for any\n"
"    errors that you find. This is a High-Mortal Zone..Consider\n"
"    youself warned.\n"
"           Maxwell the Lord of Under'Drin Mines'\n");
    set_weight(10);
    set_property("keep", "maxwell");
    set_value(0);
}


