//    Maxwell's Underground Mudlib 
//             Mine Cart Control Panel

#include "/adm/include/std.h"
#define BOULDER "/wizards/maxwell/underzone/dm24"
#define UNDER "/wizards/maxwell/underzone/"
inherit OBJECT;
string x,z,y,t,u,v,m,n,o,pos,here; 
int c1,c2,c3,p1,p2,p3,moving_cart;
object player,here2,*inv2,play,*lever_array;
void create() {
  ::create();
    set_name("panel");
    set_id( ({ "panel" }) );
    set_short("a small wall panel");
    set_long("This is a small control panel that has been placed in the "
 "wall. It consists of three levers and a small red button.\n"
 "There is also a small plate with writing.");
    set_weight(100);
    set_value(70);
    x = " ";
    z = " ";
    y = " ";
    t = "0";
    u = "0";
    v = "0";
    m = " ";
    n = " ";
    o = " ";
    c1 = 2;
    c2 = 2;
    c3 = 2;
    p1 = random(3) + 1;
    p2 = random(3) + 1;
    p3 = random(3) + 1;   
    inv2=({});
    lever_array = ({"lever","levers","at lever","at levers"});
}
void init() {
    add_action("pull_lever","pull");
    add_action("push_lever","push"); 
    add_action("check_lever","look");
    add_action("check_lever","bang bong");
}
int check_lever(string str){


    if( member_array(str,lever_array) != -1 ){
write("Each lever row has three possible horizontal positions.\n" 
      "The levers are currently in this configuration.\n "
    "\n |~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
      " |      1     2     3      |\n"
      " |     ___   ___   ___     |\n"   
      " |    |   | |   | |   | C  |\n"
      " |    | "+x+" | | "+y+" | | "+z+" | O  |\n"
      " |  M |   | |   | |   | N  |\n"
      " |  I | "+t+" | | "+u+" | | "+v+" | T  |\n" 
      " |  N |   | |   | |   | R  |\n"
      " |  E | "+m+" | | "+n+" | | "+o+" | O  |\n"
      " |    |   | |   | |   | L  |\n"
      " |    ----- ----- -----    |\n"
      " |                         |\n"
      " |                         |\n"
      "  ~~~~~~~~~~~~~~~~~~~~~~~~~\n");
      say(this_player()->query_cap_name()+" studies the levers.");
      return 1;
    }
   if(str == "plate" || str == "at plate"){
    write("The panel has this message written on it:\n\n'To operate the "
    "Under'Drin Mine Cart System, simply push "
    "or pull the levers into the proper configuration for you location "
    "in the mine and press the activation button.'\n"
    "'The proper lever configuration for section 61 is lever 1 ...'\n\n"
    "The lower half of the message has been scraped off.");
    say(this_player()->query_cap_name()+" glances at the plate.");
    return 1;
   }
  if(str == "red button" || str == "button" || str == "at button"){
   write("The small button has START stamped above it.");
   say(this_player()->query_cap_name()+" looks at the button.");
   return 1;
  }
}   
int pull_lever(string lever) {
string str;
    if(effective_light(this_player()) < -1) {
	notify_fail("It is too dark to see what your doing.\n");
	return 0;
    }
    if(!lever) {
      write("Format is 'pull lever <num>'");
      return 1;
    }
    if(sscanf(lever,"lever %s",str) ==1){ 
       if( str=="1" || str=="2" || str=="3"){

         if(str == "1" && c1 != 3){
            if(c1 == 1){
              x = " ";
              t = "0";
              pos = "middle";
            }
            if(c1 == 2){
              t = " ";
              m = "0";
              pos = "bottom";
            }
            c1 = c1 + 1;
          write("You pull lever 1 down into the "+pos+" position and it "
          "locks in place.");
        say(this_player()->query_cap_name()+" pulls lever 1 down on the panel.");
          return 1;
         }     
         if(str == "2" && c2 != 3){
            if(c2 == 1){
              y = " ";
              u = "0";
              pos = "middle";
            }
            if(c2 == 2){
              u = " ";
              n = "0";
              pos = "bottom";
            }
            c2 = c2 + 1;
          write("You pull lever 2 down into the "+pos+" position and it "
          "locks in place.");
        say(this_player()->query_cap_name()+" pulls lever 2 down on the panel.");
          return 1;
         }     
         if(str == "3" && c3 != 3){
            if(c3 == 1){
              z = " ";
              v = "0";
              pos = "middle";
            }
            if(c3 == 2){
              v = " ";
              o = "0";
              pos = "bottom";
            }
            c3 = c3 + 1;
         write("You pull lever 3 down into the "+pos+" position and it "
          "locks in place.");
        say(this_player()->query_cap_name()+" pulls lever 3 down on the panel.");
          return 1;
        }     
        write("Lever "+str+" is already all the way down");
        return 1;
      }
      write("Format is 'pull lever <num>'");
      return 1;
    }
    write("Your way off...");
    return 1;
}
int push_lever(string lever) {
string str;
    if(effective_light(this_player()) < -1) {
	notify_fail("It is too dark to see what your doing.\n");
	return 0;
    }
    if(!lever) {
      write("Format is 'push lever <num>'");
      return 1;
    }
    if(sscanf(lever,"lever %s",str) == 1) { 
       if( str=="1" || str=="2" || str=="3"){

         if(str == "1" && c1 != 1){
            if(c1 == 2){
              x = "0";
              t = " ";
              pos = "up";
            }
            if(c1 == 3){
              t = "0";
              m = " ";
              pos = "middle";   
            }
            c1 = c1 - 1;
          write("You push lever 1 into the "+pos+" position and it locks "
          "in place.");
         say(this_player()->query_cap_name()+" pushes lever 1 up on the panel.");
          return 1;
         }     
         if(str == "2" && c2 != 1){
            if(c2 == 2){
              y = "0";
              u = " ";
              pos = "up";  
            }
            if(c2 == 3){
              u = "0";
              n = " ";
              pos = "middle";
            }
            c2 = c2 - 1;
          write("You push lever 2 into the "+pos+" position and it locks "
         "in place.");
        say(this_player()->query_cap_name()+" pushes lever 2 up on the panel.");
          return 1;
         }     
         if(str == "3" && c3 != 1){
            if(c3 == 2){
              z = "0";
              v = " ";
              pos = "up";
            }
            if(c3 == 3){
              v = "0";
              o = " ";
              pos = "middle";
            }
            c3 = c3 - 1;
          write("You push lever 3 into the "+pos+" position and it locks "
          "in place.");
        say(this_player()->query_cap_name()+" pushes lever 3 up on the panel.");
          return 1;
        }     
        write("Lever "+str+" is already all the way up.");
        return 1;
      }
      write("Format is 'pull lever <num>'");
      return 1;
    }
    if(lever == "button" || lever == "red button") { 
     write("You press the red button down. It makes a mechanical click "
     "and then pops back up.");
     say(this_player()->query_cap_name()+" pushes the button on the panel.");
     if(c1 == p1 && c2 == p2 && c3 == p3){
       here=file_name(environment(this_object()));
//Decide Next Action Based On Panel Location
       play = this_player();
       //Begin Config. 1
       if(here == UNDER+"dm50"){
         if(!present("cart")){
           tell_room(here,"You can hear a mine track switch operating in "
           "the distance.");  
           player = this_player();
           call_other(UNDER+"dm9j","bring_cart");
           return 1;
         }
         if(present("fcart")){
           tell_room(here,"You hear a small clank, and the cart rolls out "
           "of the room.");
           present("fcart")->move(UNDER+"dm9j");
           tell_room(UNDER+"dm9j","A large rusty mining cart rolls into "
           "the room from the south tunnel.");
           return 1;
         }
       }
       //End Config. 1
       //Begin Config. 2
       if(here == UNDER+"dm71" || here == UNDER+"dm9c"){
//         tell_object(play,"Enter Config 2 Code. Moving = "+moving_cart);
         if(moving_cart == 1){
           tell_room(here,"A loud buzzer goes off inside the panel.");             
           write("The cart must be in use right now. Wait a few seconds "
           "and try again.");
           return 1;
         }
         if(!present("cart")){
           tell_room(here,"You can hear a mine track switch operating in "
           "the distance.");  
           player = this_player();
           if(here == UNDER+"dm71")
        present("tcart",find_object_or_load(UNDER+"dm9c"))->empty();
           if(here == UNDER+"dm9c")
        present("tcart",find_object_or_load(UNDER+"dm71"))->empty();
           return 1;
         }
         if(present("tcart")){
//           tell_object(play,"Enter Present Cart Code");
           present("tcart",environment(this_object()))->prepare_move();
           return 1;
         }
       }
       //End Config 2 
      }
      write("You sense that this is not the right lever configuration");
      return 1;   
    }

    write("Format: 'push lever <num>' Or 'push button'");
    return 1;
}
string query_combo() {
string sol,p4,p5,p6;
     p4 = ""+p1;
     p5 = ""+p2;
     p6 = ""+p3;
     sol = ("Lever1="+p4+" Lever2="+p5+" Lever3="+p6);
     return sol;
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
void cart_moving(){
    moving_cart = 1;
}
void cart_stopped(){
    moving_cart = 0;
} 

void reset() {
   ::reset();
 if(file_name(environment(this_object()))
    !="/wizards/maxwell/underzone/dm9c"
 || file_name(environment(this_object()))
    !="/wizards/maxwell/underzone/dm71"){
    p1 = random(3) + 1;
    p2 = random(3) + 1;
    p3 = random(3) + 1;
    tell_room(environment(this_object()),"You can hear a small whirring "
      "sound inside the panel. The lever activation setting must have just "
      "changed.");
  }
}   
