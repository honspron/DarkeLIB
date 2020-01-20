//    Maxwell's Underground Mudlib
//           End Of Rope

#include "/adm/include/std.h"
#define UNDER "/wizards/maxwell/underzone/dm"
inherit OBJECT;

create() {
    ::create();
   set_id(({"rope","fiber rope"}));
   set_name("rope");
   set_short("a long rope is hanging here");
    set_long("The thick rope is made from three strong strands of metals."
" Within the braids you can see wraps of gold,silver and steel wire. The "
"rope almost seems to glow slightly. The rope is attached somewhere above"
"you.");
   set_weight(50);
   set_value(50);
}
int get() { 
    write("The rope is tied at the top!");
    return 0;
}
int init(){
    ::init();
    add_action("climb_rope","climb");
}
int climb_rope(string str){
string dest;
    if(str == "rope"){
       write("You climb "+this_object()->query_property("climb_dir")+" the "
             "rope.");
       say(this_player()->query_cap_name()+" climbs "
           +this_object()->query_property("climb_dir")+" the rope.");
       dest = (this_object()->query_property("climb_dest"));
       tell_room(dest,this_player()->query_cap_name()+" climbs up the rope "
       "into the room.");
       this_player()->move(find_object_or_load(dest));
       return 1;
    }
}
