//    Maxwell's Underground Mudlib 
//          Disc for Gold Altar
#include "/adm/include/std.h"

inherit OBJECT;
 
void init() {
   ::init();
    add_action("add","add");
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
int add(string str){
string aray;
//   if(str == 0){
//     write("Add what?");
//     return 1;
//   }
   aray = aray + str;
   write("value of array is ");
   return 1;
}
