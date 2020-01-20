//    Maxwell's Underground Mudlib 
//          Silver Blade of Axe of Dulith
#include <std.h>

inherit OBJECT;
 
void create() {
  ::create();
    set_name("silver blade");
    set_id( ({ "silver blade","blade" }) );
   set_short("a sharp silver axe blade" );
    set_long("This is a sharp silver axe blade"); 
    set_weight(100);
    set_value(70);
}
int move(object dest){
string *quests;
    quests = this_player()->query_quests();
    if( (member_array("Axe of Montar",quests)) != -1 ){
      write("You have already completed this quest!");
      return 1;
    }
    else
    ::move(dest);
}
