//    Maxwell's Underground Mudlib 
//       Dwarven "Dynamite like" Zikert Dust 

#include "/adm/include/std.h"
#define BOULDER "/wizards/maxwell/underzone/dm24"
inherit OBJECT;
 
void create() {
  ::create();
    set_name("zikert dust");
    set_id( ({ "tube","zikert dust tube","zikert","dust" }) );
    set_short("a packed tube of potent zikert dust");
    set_long("This is a small tube of Zikert Dust, a mineral dust that is "
"is well known for its explosive properties. A single tube that is packed "
    "correctly can reduce a full size boulder to a pile of pebbles.\n"
    "The Dwarven Miners use this for breaking up bedrock.\n"
    "Sticking out from one end is a small fuse.");
    set_weight(100);
    set_value(70);
}
void init() {
    add_action("light","light");
    add_action("check_fuse","look"); 
}
int dyna(string str){ 
    if(str == "tube" || str == "zikert dust tube" || str == "zikert") {
    notify_fail("The  doesn't look very stable. There is something "
    "oozing out of the side of the stick. Picking it up might cause it to "
    "explode.\n"); }
}
int check_fuse(string str){
    if(str == "fuse"){
      write("The small black fuse sticks out only a inch or two. It "
      "looks like it would burn easily.");
      return 1;
    }
}
int light(string str) {
    if(effective_light(this_player()) < -1) {
	notify_fail("It is too dark to see what your doing.\n");
	return 0;
    }
 if(str=="tube" || str=="zikert dust tube" || str=="zikert" || str=="dust"){
     write("For some reason sticking a hot flame near the "
    "tube seems like an explosively stupid idea.\n");
     say(this_player()->query_cap_name()+" considers sticking a hot flame "
     "next to the dynamite.\n");
     return 1;
    }
    if(str == "fuse" || str == "small fuse") {
      if(file_name(environment(this_object())) == BOULDER) {
	write ("You light the fuse on the tube.\n");
	say(this_player()->query_cap_name()+" lights the fuse on the "
	"tube of Zikert Dust.\n", this_player());
	call_out("flare",3,this_player());
	return 1;
      }
    if(file_name(environment(this_player())) == BOULDER) {
	write("The boulder looks like it could use a good blast, but "
	"maybe you should lay the tube on the floor.");
	return 1;
     }
      write("You just gonna waste a good tube of Zikert Dust??");
      return 1;
      }
}
int flare(string fun) { 
    tell_room( "/wizards/maxwell/underzone/dm24",
"The fuse slowly starts to burn. The small flame quickly begins to gain "  
"strength. There is only a few inches left on the fuse.\n");
    call_out("blast",5,this_player());
    return 1;
}
int blast(string fun) {
   tell_room( "wizards/maxwell/underzone/dm24",
"The Zikert tube explodes with a deafening roar!!.\n"
"Large rocks are thrown through the air and the hot flames fill the small "
"room!.\n");
   call_other(BOULDER,"smokey");
   call_other(BOULDER,"echo");
  tell_room(BOULDER,"Should have made the calls");
   remove();
   return 1;
}    
