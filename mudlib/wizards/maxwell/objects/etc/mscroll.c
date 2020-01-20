//    Maxwell's Underground Mudlib
//          Duke of Montar's Scrol

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

create() {
    ::create();
   set_id(({"scroll","tomb scroll"}));
   set_name("scroll");
   set_short("a cracked and faded parchment scroll");
   set("long", "The scroll is obviously very old. The writing on it "
   "is in an ancient Dwarven script. Maybe you should try reading it.");
   set_weight(5);
   set_value(10);
}
int get() { 
    write("You try to lift the scroll off the wall, but it remains firmly "
    "attached.");
    return 0;
}
int init(){
    ::init();
    add_action("read_scroll","read");
}
int read_scroll(string str){
    if(str == "scroll" || str == "tomb scroll"){
       write("As you eyes glance at the undeciperable language, the words "
       "begin to form  into understandable phrases.\n\n"
"     'Welcome Adventurer. Alas I can only greet you in my absence with "
"a heavy heart. For the fact that you are reading this means that "
"I have failed in my attempt to recover the Axe of Montar. In "
"case you did not know I was forced to save the Axe from an invading "
"army by sending it and my trusted Mage Venkart to the temple your "
"now standing in. I was to return to the temple and recover the Axe "
"after the army was defeated and the Axe could be safely returned to "
"Montar. Evidently fate has chosen another path for me to follow.'\n"       
//
"     'The task that lays before you now is not to be taken lightly. In "
"prepration of the possibilty that I would not be able to return to "
"the temple, I ordered Venkart to create three warriors of immense "
"power to protect my beloved axe. The axe was split into three parts "
"and each part was sealed in an altar guarded by one of the warriors.\n"
"     'That is all that I will tell you. If you wish to have the "
"glorious Axe of Montar you must earn it. If you are prepared to "
"accept your fate, tell Venkart that you accept my challenge. Consider "
"yourself warned brave one.'\n\n"
"'Dwarven Duke of Montar'\n");
       return 1;
    }
}
