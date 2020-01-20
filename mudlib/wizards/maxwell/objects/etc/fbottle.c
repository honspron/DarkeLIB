//    Maxwell's Underground Mudlib
//    Dwarven Miner Helmet Fuel

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

int fuel_level;
create() {
    ::create();
   set_id(({"fuel bottle","bottle","mhelmet bottle"}));
   set_name("bottle");
   set_short("a stained metal fuel bottle");
   set("long", "This lightweight fuel bottle is made of steel. There is a "
   "small fuel level gauge on the side of it, for checking the amount of "
   "fuel left.");
   set_weight(5);
   set_value(10);
   fuel_level = 500;
}
void init() {
     ::init();
    add_action("check_fuel_level","check");    
}
int check_fuel_level(string str){
    if(str == "fuel level" || str == "fuel gauge" || str == "gauge"){
      write("The gauge on the fuel bottle shows that there is "
         +(fuel_level/3)+"Dvu of fuel left.");
      say(this_player()->query_cap_name()+" looks at the fuel gauge on "
      +this_player()->query_possessive()+" spare fuel bottle.");
      return 1;
    }
}
int query_fuel_level(){
   return fuel_level;
}

int adjust_fuel_level(int amount){
   fuel_level = (fuel_level - amount);
   return 1;
}

