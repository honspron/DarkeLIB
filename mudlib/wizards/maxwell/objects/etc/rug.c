//    Maxwell's Underground Mudlib
//           Dwarven Rug

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;
int not_found;

create() {
    ::create();
   set_id(({"rug","woven rug"}));
   set_name("rug");
   set_short("a woven rug");
   set("long", "This rug is made from some sort of thick fabric. The "
   "pattern on it is shaped like a large spiral.");
   set_weight(50);
   set_value(100);
   not_found = 0;
}
init(){
    ::init();
    add_action("search_rug","search");
}
int search_rug(string str){
    if(str == "rug" && not_found == 0){
      write("You find a small pouch hidden on the bottom of the rug! It "
      "contains a small key which you quickly grab.");
      new("/wizards/maxwell/objects/etc/rkey")->move(this_player());
      not_found = 1;
      return 1;
    }
}
reset(){
   ::reset();
   not_found = 0;
} 
