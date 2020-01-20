//    Maxwell's Underground Mudlib 
//         Status Checker
#include "/adm/include/std.h"

inherit OBJECT;
 
void create() {
  ::create();
    set_name("status rod");
    set_id( ({ "status rod","status","rod" }) );
   set_short("a status rod" );
    set_long("This is a status checker for monitoring health and "
    "magic levels. Just type <check> ");
    set_weight(100);
    set_value(70);
}
void init() {
    add_action("check","check");
}
int check(string fun){
   write("Health "+this_player()->query_hp()+" Magic "
   +this_player()->query_mp());
     return 1;
}
