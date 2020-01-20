#include <move.h>

inherit "/std/Object";

int move(object dest) {
  if(living(dest)) return MOVE_NOT_ALLOWED;
  else return ::move(dest);
}

void create() {
  ::create();
  set_name("cask");
  set_id(({ "cask", "wine cask" }) );
  set_short("A cask of wine");
  set_long(
"This cask may be used to fill waterskins with wine for communion ceremonies "
"or general consumption.  A donation of 5 silver is requested for this "
"generous service.  Use fill <object> to fill something with wine.");
  return;
}

void init() {
  ::init();
  add_action("fill_vessel", "fill");
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
    write("You can't fill "+article(str)+" with wine!");
    return 1;
  }
  if((int)this_player()->query_money("silver") < 5) {
    write("You do not have the requested donation of 5 silver.");
    return 1;
  }
  if(ob->full()) {
    write("That waterskin is full already.");
    return 1;
  }
  this_player()->add_money("silver", -5);
  ob->fill("wine", 15, 10);
  write("You fill the waterskin.");
  message("other_action", (string)this_player()->query_cap_name() +
	  " fills a waterskin with wine from the cask.",
	  environment(this_player()), ({ this_player() }) );
  return 1;
}

int clean_up() { return 0; }
