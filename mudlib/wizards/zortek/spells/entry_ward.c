#include <std.h>
inherit OBJECT;

string owner, caster;
int duration;

void init() {
  if((string)this_player()->query_true_name() == owner ||
     (string)this_player()->query_true_name() == caster ||
     archp(this_player()) ) {
    add_action("sever_me", "sever");
  }
  if(duration && owner && caster)
  message("clairvoy", 
  "<o> <o>:["+environment(this_object())->query_short()+"]:"+capitalize(this_player()->query_true_name())+" entered.", find_living(owner));
  if(--duration < 1) {
    this_object()->remove();
  }
}
void create() {
  set_name("entry_ward");
  duration = 5;
}
void set_up(string cast, string own, int power) {
  caster = cast;
  owner = own;
  duration = 3+power * power * power;
}
int sever_me(string str) {
  if(str != "entry ward") {
    notify_fail("Sever what?\n");
    return 0;
  }
  this_object()->remove();
  return 1;
}
void remove() {
  if(!owner || !caster) {
    ::remove();
    return;
  }
  message("clairvoy",
    "<-> <->:["+environment(this_object())->query_short()+"]: ", find_living(owner));
  ::remove();
}
