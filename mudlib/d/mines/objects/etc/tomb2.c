//    Maxwell's Underground Mudlib 
//          Tomb of Dwarf Crypt
#include <std.h>

inherit OBJECT;
int x; 
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
    x = 0;
}
void init() {
     ::init();
     add_action("push","push");
}
int push(string str){ 
    if(str == "slab" && x==0){
      tell_object(this_player(),"You push the slab to the side.");
      call_out("open_message",1,this_object());
      call_other(environment(this_object()),"exit");
      x = x+1;
      return 1;
    }
    tell_object(this_player(),"The slab has already been pushed aside!");
return 1;
}
int get() { 
    if(query("get message")) write(query("get message"));
    return 0;
}
int close_message(){
    set_long("The tomb is made of solid marble. Carved into the marble "
"are strange looking words and symbols. The tomb looks very holy and "
"sacred. One of the symbols depicts a demon of some sort protecting the "
"the tomb from trespassers.\n"
"One side of the tomb has a large granite slab on it.");
return 1;
}
int open_message(){
    set_long(this_object()->query_long()+"\nOne side of the tomb has been "
"pushed open");
return 1;
}
void reset() {
   ::reset();
    x = 0;
    call_out("open_message",1,this_object());
}
