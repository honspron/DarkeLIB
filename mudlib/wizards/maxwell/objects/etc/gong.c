//    Maxwell's Underground Mudlib
//           Dwarven Summoning Gong

#include "/adm/include/std.h"
#include "under.h"
inherit OBJECT;

string here;
int num_strikes;
create() {
    ::create();
   set_id(({"gong","golden gong"}));
   set_name("gong");
   set_short("a huge golden gong");
   set("long", "This ancient gong appears to have been made by very "
"skilled craftsmen. The front of the disc is engraved with detailed "
"drawings of the Dwarven Empire and the City Of Montar.\n"
"Attached to one side of the gong is a large golden mallet, wrapped in "
"dark oiled leather.");
   set_weight(500000);
   set_value(0);
   num_strikes = 1;
}
int get() { 
    write("You try to roll the gong off of its stand, "
           "but it is too heavy.");
    return 0;
}
int init(){
    ::init();
    here = file_name(environment(this_object()) );
    add_action("look_gong","look");
    add_action("strike_gong","strike");
}
int look_gong(string str){
    if(str == "mallet" || str == "at mallet"){
     write("The finely crafted Striking Mallet is quite beautiful.");
     return 1;
    }
}
int strike_gong(string str){

    if(str == "gong" || str == "golden gong"){
      write("You strike the gong with the heavy mallet!"); 
      say(this_player()->query_cap_name()+ " strikes the gong with the "
     "heavy mallet!");
     tell_room(here,"A low pitched tone echoes through the temple.");
     if(num_strikes != 3 || read_file(UNQST+"axe_owner") != "nobody") {
       num_strikes = num_strikes + 1;
        return 1;
     }
     call_out("bring_venkart",3,this_object());
     num_strikes = num_strikes + 1;
     return 1;
    }
    write("Strike what?");
    return 1;
}
int bring_venkart(){
    tell_room(here,"A cloud of black gas forms in front of you!\n"
    "A hooded Mage appears inside the cloud.");
    new(UNMON+"venkart")->move(here);
    (present("venkart"))->tell_room(here,"Venkart says Why have you "
    "disturbed my Temple?");
    return 1;
}
int query_strikes(){
    return num_strikes;
}
void save_me(){
    save_object("/wizards/maxwell/sgong",1);
    return;
}
void reset(){
     ::reset();
     num_strikes = 0;
     return;
}  
