//     Maxwell's Underground Mudlib
//            Moving Mine Cart

#define UNDER "/wizards/maxwell/underzone/dm"
#define BEGIN "/wizards/maxwell/underzone/dm2"
#define END "/wizards/maxwell/underzone/dm66"
#include "/adm/include/std.h"
inherit "/std/bag_logic";
int x,dir,y;
object crt;

void init() {
    ::init();
    add_action("pull", "pull");
}
void create() {
    set_id( ({"cart"}) );
    set_name("cart");
    set("short", "a large mining cart");
    set_weight(300);
    set("long", 
    "This is a large rusty mining cart. It rolls along the mining tracks " 
    "on four large steel wheels. The cart looks like it could hold "
    "a large amount of rocks.\n");
    set_value(50);
    set_max_internal_encumbrance(5000);
    x = 1;
    dir = 1;
}
int pull(string str) {
   if(str == "lever"){
     if(y == 0){
       write("You pull back on the greasy lever and it locks in place.");
       if(file_name(environment(this_object())) == BEGIN) {
         x = 12;
         crt = present("cart");
         call_out("exit",5,this_object());
         y = 1;
         return 1;
       }
       if(file_name(environment(this_object())) == END) {
         x = 1;
         crt = present("cart");
         call_out("exit",5,this_object());
         y = 1;
         return 1;
       }
       write("There is no mine track.");
       return 1;
     }
     write("The lever has already been pulled.");
     return 1;
    }
    write("Pull what?");
    return 1;
}
int exit(string fun){
  if(x == 1){
    tell_room(UNDER+"66","The mine cart begins to "
    "move. It picks up speed and rolls out the eastern tunnel.");
    tell_room(UNDER+"65","A mine cart rolls into the "
    "tunnel from the west.");
    new("/wizards/maxwell/objects/etc/pore.c")->move(crt);
    crt->move(find_object_or_load(UNDER+"65"));
    x = x + 1;
    dir = 1;
    call_out("exit",10,this_object());
    return 1;
    }
if(x == 2){
    if(dir == 1){
     tell_room(UNDER+"65","The mining cart slowly "
     "rolls into the eastern tunnel.");
     tell_room(UNDER+"64","A mine cart rolls into the "
     "tunnel from the west.");
     crt->move(find_object_or_load(UNDER+"64"));
     x = x + 1;
     call_out("exit",10,this_object());
     return 1;
    }
    tell_room(UNDER+"65","The cart moves down "
    "into the smaller tunnel an quickly rolls out of sight.");
    tell_room(UNDER+"66","A mine cart rolls into the "
    "tunnel from the east and grinds to a halt.");
    crt->move(find_object_or_load(UNDER+"66"));
    x = x - 1;
    call_out("exit",10,this_object());
    return 1;
 }
 if(x == 3){
   if(dir == 1){
    tell_room(UNDER+"64","The mine cart rolls "
    "east.");
    tell_room(UNDER+"63","A mine cart rolls into the "
    "tunnel from the west.");
    crt->move(find_object_or_load(UNDER+"63"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"64","The mine cart rolls down into the tunnel.");
   tell_room(UNDER+"65","A mine cart rolls into the "
   "tunnel from the upper tunnel.");
   crt->move(find_object_or_load(UNDER+"65"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 4){
   if(dir == 1){
    tell_room(UNDER+"63","The cart rolls east");
    tell_room(UNDER+"62","A mine cart rolls into the "
    "tunnel from the west.");
    crt->move(find_object_or_load(UNDER+"62"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"63","The cart rolls west");
   tell_room(UNDER+"64","A mine cart rolls into the "
   "tunnel from the east.");
   crt->move(find_object_or_load(UNDER+"64"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 5){
   if(dir == 1){
    tell_room(UNDER+"62","The cart rolls east");
    tell_room(UNDER+"9","A mine cart rolls into the "
    "tunnel from the west.");
    crt->move(find_object_or_load(UNDER+"9"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"62","The cart rolls west");
   tell_room(UNDER+"63","A mine cart rolls into the "
   "tunnel from the east.");
   crt->move(find_object_or_load(UNDER+"63"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 6){
   if(dir == 1){
    tell_room(UNDER+"9","The cart rolls north");
    tell_room(UNDER+"8","A mine cart rolls into the "
    "tunnel from the south.");
    crt->move(find_object_or_load(UNDER+"8"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"9","The cart rolls west");
   tell_room(UNDER+"62","A mine cart rolls into the "
   "tunnel from the east.");
   crt->move(find_object_or_load(UNDER+"62"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 7){
   if(dir == 1){
    tell_room(UNDER+"8","The cart rolls northeast");
    tell_room(UNDER+"6","A mine cart rolls into the "
    "tunnel from the southwest.");
    crt->move(find_object_or_load(UNDER+"6"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"8","The cart rolls south");
   tell_room(UNDER+"9","A mine cart rolls into the "
   "tunnel from the north.");
   crt->move(find_object_or_load(UNDER+"9"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 8){
   if(dir == 1){
    tell_room(UNDER+"6","The cart rolls northeast");
    tell_room(UNDER+"5","A mine cart rolls into the "
    "tunnel from the southwest.");
    crt->move(find_object_or_load(UNDER+"5"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"6","The cart rolls southwest.");
   tell_room(UNDER+"8","A mine cart rolls into the "
   "tunnel from the northeast.");
   crt->move(find_object_or_load(UNDER+"8"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 9){
   if(dir == 1){
    tell_room(UNDER+"5","The cart rolls northeast");
    tell_room(UNDER+"4","A mine cart rolls into the "
    "tunnel from the southwest.");
    crt->move(find_object_or_load(UNDER+"4"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"5","The cart rolls southwest");
   tell_room(UNDER+"6","A mine cart rolls into the "
   "tunnel from the northeast.");
   crt->move(find_object_or_load(UNDER+"6"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 10){
   if(dir == 1){
    tell_room(UNDER+"4","The cart rolls southeast");
    tell_room(UNDER+"3","A mine cart rolls into the "
    "tunnel from the northwest.");
    crt->move(find_object_or_load(UNDER+"3"));
    x = x + 1;
    call_out("exit",10,this_object());
    return 1;
   }
   tell_room(UNDER+"4","The cart rolls southwest");
   tell_room(UNDER+"5","A mine cart rolls into the "
   "tunnel from the northeast.");
   crt->move(find_object_or_load(UNDER+"5"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 11){
   if(dir == 1){
    tell_room(UNDER+"3","The cart rolls southeast");
    tell_room(UNDER+"2","A mine cart rolls into the "
    "tunnel from the northwest.");
    crt->move(find_object_or_load(UNDER+"2"));
    x = x + 1;
    call_out("empty",10,this_object());
    return 1;
   }
   tell_room(UNDER+"3","The cart rolls northwest");
   tell_room(UNDER+"4","A mine cart rolls into the "
   "tunnel from the southeast.");
   crt->move(find_object_or_load(UNDER+"4"));
   x = x - 1;
   call_out("exit",10,this_object());
   return 1;
 }
 if(x == 12){
   tell_room(UNDER+"2","The cart begins to roll "
  "into the northwest tunnel.");
   tell_room(UNDER+"3","A mine cart rolls into the "
   "tunnel from the southeast.");
   crt->move(find_object_or_load(UNDER+"3"));
   x = x - 1;
   dir = 0;
   call_out("exit",10,this_object());
   return 1;
   }
}
int empty() {
  object ore1;
  if(present("ore",this_object())) {
    tell_room(UNDER+"2","The cart tilts up and dumps a pile of ore on the "
    "ground.");
    ore1 = (present("ore",this_object()));
   if(!present("ore",environment(this_object()))) {
     ore1->move(UNDER+"2");
     call_out("exit",5,this_object());
     return 1;
   }
   ore1->remove();   
   call_out("exit",5,this_object());
   return 1;
  }
  tell_room(UNDER+"2","The cart tilts up, but it is empty.");
  call_out("exit",5,this_object());
  return 1;
}
  
