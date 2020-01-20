#include <move.h>

inherit "/std/Object";

int move(object dest) {
  if(objectp(dest) && living(dest)) return MOVE_NOT_ALLOWED;
  return ::move(dest);
}

void create() {
  ::create();
  set_name("key rack");
  set_id( ({ "rack", "key rack" }) );
  set_short("A key rack");
  set_long(
"Here you can get a chest key for 2 gold.  It will, of course, "
"only open YOUR chests.  Type 'take key'.");
  return;
}

void init() {
  ::init();
  add_action("take_key", "take");
  return;
}

int take_key(string str) {
  object ob;
  
  if(lower_case(str) != "key")
    return notify_fail("Take what?\n");
  if((int)this_player()->query_money("gold") < 2) {
    write("You need 2 gold to get a key.");
    return 1;
  }
  this_player()->add_money("gold", -2);
  ob = new("/std/Object");
  ob->set_property("no save", 1);
  ob->set_name("key");
  ob->set_short(capitalize((string)this_player()->query_name()) +
        "'s chest key");
  ob->set_long("This is an iron key designed to work in a chest lock.");
  ob->set_id( ({ "key", "chest key", (string)this_player()->query_name()+" chest key" }) );
  ob->set_weight(15);
  ob->set_property("is key", 1);
  ob->move(this_player());
  write("You take your key from the rack.");
  return 1;
}
