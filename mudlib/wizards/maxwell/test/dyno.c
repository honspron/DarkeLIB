//    Maxwell's Underground Mudlib 
//              Dynamite

#include "/adm/include/std.h"
#define BOULDER "/wizards/maxwell/underzone/dm24"
inherit OBJECT;
 
void create() {
  ::create();
    set_name("dynamite");
    set_id( ({ "dynamite" }) );
    set_short("a stick of dynamite");
    set_long("This is a small stick of potent dynamite. The dynamite is "
    "wrapped in a thick paper tube, although you can see some kinda sticky "
    "substance leaking out of one end.\n"
    "Sticking out from one end is a small fuse.");
    set_weight(100);
    set_value(70);
}
void init() {
    add_action("light","light");
    add_action("check_fuse","look"); 
}
int dyna(string str){ 
    if(str == "dynamite") {
    notify_fail("The dynamite doesn't look very stable. There is something "
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
    if(str == "dynamite") {
     write("For some reason sticking a hot flame near the "
    "dynamite seems like an explosively stupid idea.\n");
     say(this_player()->query_cap_name()+" considers sticking a hot flame "
     "next to the dynamite.\n");
     return 1;
    }
    if(str == "fuse") {
      if(file_name(environment(this_object())) == BOULDER) {
	write ("You light the fuse on the dynamite.\n");
	say(this_player()->query_cap_name()+" lights the fuse on the "
	"dynamite.\n", this_player());
	call_out("flare",3,this_player());
	return 1;
      }
    if(file_name(environment(this_player())) == BOULDER) {
	write("The boulder looks like it could use a good blast, but "
	"maybe you should lay the dynamite on the floor.");
	return 1;
     }
      write("You just gonna waste a good stick of dynamite??");
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
"The dynamite explodes with a deafening roar!!.\n"
"Large rocks are thrown through the air and the hot flames fill the small "
"room!.\n");
   call_other("/wizards/maxwell/underzone/dm24","smokey");
   call_other("/wizards/maxwell/underzone/dm24","echo");
   remove();
   return 1;
}    
