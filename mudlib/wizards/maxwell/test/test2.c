//    Maxwell's Underground Mudlib 
//          Disc for Gold Altar
#include "/adm/include/std.h"

inherit OBJECT;
string aray1,aray2; 
void init() {
   ::init();
      add_action("test", (: call_other, this_object(), "test" :) );
//    add_action("test","test");
}
void create() {
  ::create();
    set_name("disc");
    set_id( ({ "disc" }) );
   set_short("A small steel disc" );
    set_long("This is a small steel disc. It has strange symbols "
"burned into its surface.\n");
    set_weight(30);
    set_value(70);
}
int droppy(string fun){
    move("/wizards/maxwell/underzone/dm28");
    return 1;
}
int dud(string fun){
    remove();
     return 1;
}
int test(object who){
string who2;
 //    who = this_object();
     who2 = who->query_name();
//   if(str == 0){
//     write("Add what?");
//     return 1;
//  }
//   aray1 = aray2 + str;
//   aray2 = aray1;
   write("value of array is "+who2);
//   str->move("/wizards/maxwell/workroom");
   return 1;
}
