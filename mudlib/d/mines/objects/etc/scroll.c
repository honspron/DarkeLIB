//    Maxwell's Underground Mudlib
//           Dwarven Dust Tube Chart

#include <std.h>
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
"    'During the time of the seige of Montar, the powerful Dwarven Axe of "
"Dulith was seperated into three pieces by the great Dwarven Mage "
"Venkart, under order of the Royal Duke of Montar. The three pieces were "
"entrusted to three guardians, summoned from other dimensional "
"realites by Venkart the Mage.\n"
"     Just before the invading forces broke through into "
"the city, the guardians and Venkart were secretly moved from Montar to a "
"sacred temple somewhere deep within the Great Mountains.\n"
"     It was widely believed that the Duke intended to retrieve the axe "
"after reinforcements arrived from the Northern realm. However, they "
"came too late. Montar had been burned to the ground days before, and "
"the location of the Mountain Temple was lost forever in the ashes and "
"blackened stones.'\n\n"
"             'Jencob, Offical Scribe of The City Of Montar\n"
"      May the souls of my fellow Dwarves find peace in the afterlife.'" );
       return 1;
    }
}
