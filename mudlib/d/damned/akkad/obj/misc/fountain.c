#include <move.h>
 
inherit "/std/Object";
 
 int move(object desti) {
  if(desti->is_player()==1) return MOVE_NOT_ALLOWED;
  if(desti->is_player()!=1) return ::move(desti);
 }
 
 
void create() {
  ::create();
  set_name("fountain");
  set_id(({"fountain", "small fountain"}) );
  set_short("A %^CYAN%^BOLD%^small crystal clear fountain%^BOLD%^%^MAGENTA%^");
  set_long("This small fountain gurgles with ice cold water.");
  set_weight(999999999999);
}
 
void init() {
  ::init();
  add_action("fill_vessel", "fill");
  add_action("do_drink", "drink");

  return;
}
 
int fill_vessel(string str) {
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
  if(ob->full()) {
    write("That waterskin is full already.");
    return 1;
  }
  ob->fill("water", 5, 0);
  write("You fill the waterskin.");
  message("other_action", (string)this_player()->query_cap_name() +
        " fills a waterskin with water from the fountain.",
        environment(this_player()), ({ this_player() }) );
  return 1;
}
 

int do_drink(string str) {
   if(!str) {
      notify_fail("What do you want to drink?\n");
      return 0;
  }
   if(str != "water" && str != "fountain") {
      return 0;
   }
if(!this_player()->add_quenched(20))
{
notify_fail("You are too bloated to drink!\n");
return 0;
}
this_player()->add_quenched(60);
   write("You bend down and drink the clear water from the fountain.\n");
   say(this_player()->query_cap_name()+" gulps water from the fountain.\n",
         this_player());
   return 1;
}
