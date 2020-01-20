//   Maxwell's Underground Mud Library   
//              Skeleton   

#include <std.h>
inherit OBJECT;
int x;
object obj;
void create() {
    seteuid("skeleton");
    set_id( ({"skeleton"}) );
    set_name("skeleton");
    set_short("a rotting skeleton");
    set_long("A decomposed skeleton is laying on the altar. It is still "
"wrapped in its tattered burial garments. The fibers of the garments "
"have rotted away almost to nothing, exposing the dry and cracked bones "
"beneath.");
    set_weight(100);
    set_value(0);
    x = 1;
//    set_max_internal_encumbrance(100);
}
void init(){
    ::init();
    add_action("kick", "kick");
}
int kick(string str){
  if((str == "skeleton" || str == "garments") && x == 1){
    write("You search the rotting garments and find an old bone and gold "
    "necklace.");
//    say(this_player()->query_cap_name()+" searches the skeleton and finds "
// "something in the garments.");
  obj = new("/wizards/maxwell/objects/etc/bneck");
  obj->move(environment(this_object()));
    x = 0;
    return 1;
 }
 write("You find nothing.");
 say(this_player()->query_cap_name()+" searches around, but finds nothing.");  
 return 1;
}
int get(){
   write("The skeleton would break apart if you tried to move it.");
   return 0;
}
void reset() {
    ::reset();
   if(!present("necklace")) x = 1;
}

