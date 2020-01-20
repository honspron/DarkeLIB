//    Maxwell's Underground Mudlib 
//            Combo Safe

#include "/adm/include/std.h"
inherit OBJECT;

int safe_open,*combo,uncovered,x1,x2,x3;
mixed *current_combo;
void create() {
  ::create();
    set_name("steel safe");
    set_id( ({ "steel safe","safe" }) );
   set_short("an old steel safe (closed)" );
    set_long("This old steel safe is built into the wall. It has 3 "
      "dials with numbers and a lever to open the safe.\n"
      "You can 'turn dial <num> <up/down>',\n"
      "        'look at dials',\n"
      "        'open safe',\n"
      "        'close safe'\n");
    set_weight(100000);
    set_value(70);
    combo = ({});
    current_combo = ({0,0,0});
    uncovered = 1;
    x1 = random(10);
    x2 = random(10);
    x3 = random(10);
    reset();
}
init(){
    ::init();
    if( uncovered == 1){
       add_action("open_safe","open");
       add_action("close_safe","close");
       add_action("turn_dial","turn");
       add_action("look_at","look");
    }
}
int look_at(string str){
mixed x4,x5,x6,x7,x8,x9;
    if(str == "lever" || str == "at lever"){
      write("The steel lever opens the safe when the combo is set right.");
     say(this_player()->query_cap_name()+" looks at the lever on the safe.");
      return 1;
    }
    if(str == "dials" || str == "dial" || str == "at dials" 
      || str == "at dial"){
     say(this_player()->query_cap_name()+" studies the dials on the safe.");
      if(x1 == 0 || x1 == 9){
         if(x1 == 0){
           x5 = " ";
           x4 = x1 + 1;
         }
         else {
           x5 = x1 - 1;
           x4 = " "; 
         }
      }
      else {
         x4 = x1 + 1;
         x5 = x1 - 1;
      }
      if(x2 == 0 || x2 == 9){
        if(x2 == 0){
         x6 = x2+1;
         x7 = " ";
        }
        else {
         x6 = " ";
         x7 = x2 - 1;
        }      
      }
      else {
        x6 = x2 + 1;
        x7 = x2 - 1;
      } 
      if(x3 == 0 || x3 == 9){
        if(x3 == 0){ 
         x9 = " ";
         x8 = x3 + 1;
        }
        else {
         x8 = " ";
         x9 = x3 - 1;
        }
      }
      else {
        x8 = x3 + 1;
        x9 = x3 - 1;
      }
      write("\n"
     "   _________________________________\n"
     "   |                               |\n"
     "   |        Fenton Locksmith       |\n"
     "   |      _____  _____  _____      |\n"   
     "   |      | "+(x4)+" |  | "+(x6)+" |  | "+(x8)+" |      |\n"
     "   |     -| "+(x1)+" |--| "+(x2)+" |--| "+(x3)+" |-     |\n"
     "   |      | "+(x5)+" |  | "+(x7)+" |  | "+(x9)+" |      |\n"
     "   |      ~~~~~  ~~~~~  ~~~~~      |\n"
     "   |                               |\n"
     "   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
     return 1;
   }
}   
int open_safe(string str){
int x,y;
    if(str == "safe" || str == "steel safe"){
      if( uncovered != 1){
        write("What safe?");
        return 1;
      }
      if(safe_open != 1) {
         x = 0;         
           if(x1 == combo[0])
               x = x + 1;
           if(x2 == combo[1])
               x = x + 1;
           if(x3 == combo[2])
               x = x + 1;
         if(x == 3){
           write("You twist the lever and open the safe!");
           say(this_player()->query_cap_name()+" twists the lever on the "
              "safe and the steel door opens!");
           set_short("an old steel safe (open)" );
           safe_open = 1;
         }
         else {
           write("You twist the lever but the safe is still locked!");
           say(this_player()->query_cap_name()+" twists the lever on the "
               "safe, but it is still locked tight.");
         }
         return 1;
      }
      else {
       write("The safe is already open!");
       return 1;
      }
   }
}
int close_safe(string str){
int w;
    if(str == "safe" || str == "steel safe"){
       if( safe_open == 1){
         write("You close the safe and spin the dials.");
         say(this_player()->query_cap_name()+" closes the safe and spins "
            "the dials.");
         set_short("an old steel safe (closed)" );
         x1 = random(10);
         x2 = random(10);
         x3 = random(10);
         safe_open = 0;
       }
       else
         write("The safe isn't open!");
       return 1;
    }
}
int turn_dial(string str){
 int turned,dial_num,num,value;
 mixed *old_combo;
 string turn_dir;
    if(str == "dial"){
        write("The format is 'turn dial <num> <up/down>'");
        return 1;
    }
    if(sscanf(str,"dial %d %s",dial_num,turn_dir)){
      if( (dial_num >= 1 && dial_num <=3) &&
          (turn_dir == "up" || turn_dir == "down") ){
        turned = 0;
        if(dial_num == 1)
           value = x1;
        if(dial_num == 2)
           value = x2;
        if(dial_num == 3)
           value = x3;
        if(turn_dir == "up" && ( value > 0) ){
            value = value - 1;
            turned = 1;
        }
        if(turn_dir == "down" && (value < 9) ){
            value = value + 1;
            turned = 1;
        }
        if( turned == 1){
            write("You turn dial "+dial_num+" "+turn_dir+" to "+value);
            say(this_player()->query_cap_name()+" turns dial "+dial_num);
            if(dial_num == 1)
               x1 = value;
            if(dial_num == 2)
               x2 = value;
            if(dial_num == 3)
               x3 = value;
        }
        else {       
           write("Dial "+dial_num+" won't turn further in that direction.");
           say(this_player()->query_cap_name()+" tries to turn dial "+
                              dial_num);
        }
      }
      else
        write("The format is 'turn dial <num> <up/down>'");
      return 1;
    }
}
mixed query_combo(){
    return ("The combo is "+combo[0]+" "+combo[1]+" "+combo[2]);
}
reset(){
int w;
    ::reset();
    w = 0;
    combo = ({});
    while( w < 3){
      combo += ({random(10)});
      w = w + 1;
    }
}       
  
