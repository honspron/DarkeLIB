//   Maxwell's Underground Mudlib
//   Dwarf Well

#include <move.h>

inherit "/std/Object";

int move(mixed dest) {
    if(objectp(dest) && living(dest) && !wizardp(dest)) return
      MOVE_NOT_ALLOWED;
    return ::move(dest);
}
void create() {
  ::create();
  set_name("well");
  set_id(({ "well", "stone well" }) );
  set_short("a granite stone well filled with water");
  set_long("The well is made from stacked blocks of solid granite. There "
    "is some sort of waxy sealant between the blocks, although a little "
     "water still trickles out from several cracks.");
}
void init() {
  ::init();
  add_action("fill_object", "fill");
  add_action("drink_water", "drink");
}
int drink_water(string str){
  if(!str){
    write("Drink what?");
    return 1;
  }
  if(str == "water" || str == "well"){
    write("You drink some of the water in the well."); 
    say(this_player()->query_cap_name()+" drinks from the well.");
    this_player()->add_quenched(random(15));
//    if(random(100) < 10){
//      write("You can feel a strange sensation in your mouth!"); 
//      this_player()->add_mp(random(15));
//    }
    return 1;
  }
}
int fill_object(string str) {
object ob;
  ob = present(str, this_player());
  if(!ob) {
    write("You don't have "+article(str)+".");
    return 1;
  }
  if(!ob->id("water skin")) {
    write("You can't fill "+article(str)+" with water!");
    return 1;
  }
  if(ob->full()  > 0) {
    write("That waterskin isn't empty.");
    return 1;
  }
  ob->fill("water", 6, 0);
  write("You fill the waterskin with the well water.");
  say(this_player()->query_cap_name()+" fills a waterskin with water "
      "from the well.");
  return 1;
}


