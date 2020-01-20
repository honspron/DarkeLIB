#include <std.h>
inherit "/std/bag_logic";
int i;
string *room;
void create(){

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
    room = ({ "room1","room2","room3","room4","room5" });
    i = 0;
}
void init() {
    ::init();
    add_action("check", "check");
}
int check(){
int current_time,delay_time;
    write("Begin Test");
    call_out("mov",3,this_object());
    return 1;
}
int mov(string fun){    
int x;
    write("Pass "+i);
    x = sizeof(room);
    if( i <= x){
      write("Movement to "+room[i]);
      i = i + 1;
      call_out("mov",3,this_object());
    }
    write("Pass "+i);
    return 1;
}

