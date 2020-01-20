//    Maxwell's Underground Mudlib 
//          Tomb of Dwarf Crypt
#include <std.h>
#include <under.h>

inherit OBJECT;
int x; 
string here;
object tomb;
void create() {
  ::create();
    set_name("tomb");
    set_id( ({ "tomb" }) );
    set_short("a solid marble tomb" );
    set_long("The tomb is made of solid marble. Carved into the marble "
"are strange looking words and symbols. The tomb looks very holy and "
"sacred. One of the symbols depicts a demon of some sort protecting the "
"the tomb from trespassers.\n"
"The side of the tomb has a solid granite slab on it.");
    set_weight(100000);
    set_value(0);
    x = 1;
    tomb = this_object();
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
void init() {
     ::init();
     add_action("push","push");
     add_action("look_slab","look");
}
int look_slab(string str){
    if(str == "slab"){
      if(x == 0)
        write("The large granite slab has been pushed aside.");
      else
        write("The large granite slab is sealed against the tomb.");
      return 1;
     }
}
int auto_open(){
   here = file_name(environment(this_object()));
   tell_room(environment(this_object()),"The side of the tomb groans "
    "as a slab is pushed aside, revealing a secret staircase inside!");
   set_long("The tomb is made of solid marble. Carved into the marble "
       "are strange looking words and symbols. The tomb looks very holy "
       "and sacred. One of the symbols depicts a demon of some sort "
       "protecting the tomb from trespassers.\n"
       "A large slab on the side of the tomb has been pushed aside, "
       "revealing a dark staircase.");
   if( here == (UNDER+"dm42")){
     find_object(here)->add_exit(UNDER+"dm44","down");       
//     find_object(here)->set_pre_exit_functions(({"down"}),({"owner_check"}));    
   }
   if( here == (UNDER+"dm43"))
      find_object(here)->add_exit(UNDER+"dmc1","down");
   x = 0;
   return 1;
}   

int push(string str) {
 here = file_name(environment(this_object()));
 if(str == "slab") {
   if(x == 0) {
   write("The slab has already been pushed aside.");
   return 1;
   }
   say("A loud grating sound rumbles through the room as "
      +this_player()->query_cap_name()+" pushes the heavy slab to the "
      "side, revealing a hidden staircase.\n"); 
   write("You push the stone slab to the side and reveal a set of steps "
        "that go down inside the tomb.\n");
   tell_room(here,"A large gust of decaying wind blows out of the "
       "open tomb.\n");
   if( here == (UNDER+"dm42")){
     environment(tomb)->add_exit(UNDER+"dm44","down"); 
//     environment(tomb)->set_pre_exit_functions(({"down"}),
//                          ({"owner_check"})); 
      x = 0;
      call_other(UNDER+"dm44","otherside");
    }
   if( here == (UNDER+"dm43")){
      environment(tomb)->add_exit(UNDER+"dmc1","down");
      x = 0;
      call_other(UNDER+"c1","otherside");
    }
   set_long("The tomb is made of solid marble. Carved into the marble "
       "are strange looking words and symbols. The tomb looks very holy "
       "and sacred. One of the symbols depicts a demon of some sort "
       "protecting the tomb from trespassers.\n"
       "A large slab on the side of the tomb has been pushed aside, "
       "revealing a dark staircase.");
   x = 0;
   return 1;  
  }
  write("push what?");
  return 1;
} 
int exit(){

   return 1;
}
void reset() {
   ::reset();
    x = 1;
    set_long("The tomb is made of solid marble. Carved into the marble "
"are strange looking words and symbols. The tomb looks very holy and "
"sacred. One of the symbols depicts a demon of some sort protecting the "
"the tomb from trespassers.\n"
"One side of the tomb has a large granite slab on it.");
}


