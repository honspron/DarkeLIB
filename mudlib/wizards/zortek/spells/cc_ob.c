#include <move.h>
#include <std.h>
inherit OBJECT;

string owner, caster, target;
int duration, power, can_move;

void show_loc();

void init() {
  if((string)this_player()->query_true_name() == owner ||
     (string)this_player()->query_true_name() == caster ||
     archp(this_player()) ) {
    add_action("sever_me", "sever");
  }
}
void create() {
  set_name("cc_ob");
  duration = 5;
  can_move = MOVE_OK;
}
void set_up(string cast, string own, string targ, int pow) {
  caster = cast;
  owner = own;
  target = targ;
  power = pow;
  duration = 3+power * power * power;
  move_object(find_living(owner));
  can_move = MOVE_NOT_ALLOWED;
  show_loc();
}
int sever_me(string str) {
  if(str != "continual clairvoyance") {
    notify_fail("Sever what?\n");
    return 0;
  }
  this_object()->remove();
  return 1;
}
void remove() {
  can_move = MOVE_OK;
  if(!owner || !caster) {
    ::remove();
    return;
  }
  message("clairvoy",
    "<-> <->:["+capitalize(target)+"]: ", find_living(owner));
  ::remove();
}
void show_loc() {
  object who;
	if(!environment(find_living(target))) {
    message("clairvoy",
      "<o> <o>:["+capitalize(target)+"]: UNKNOWN LOCATION (The Void)",
      find_living(owner));
    if(--duration > 1)
      delayed_call("show_loc", 10-power);
    else
      this_object()->remove();
    return;
  }
  if(who = find_living(target)) {
    if(!find_living(owner)->query_verbose())
      message("clairvoy",
        "<o> <o>:["+capitalize(target)+"]: "+environment(who)->query_short()+
        "  "+environment(who)->query_short_exits(), 
        find_living(owner));
    else
      message("clairvoy",
        "<o> <o>:["+capitalize(target)+"]: \n%^RESET%^"+
        environment(who)->query_long()+environment(who)->query_short_exits(), 
        find_living(owner));
    if(--duration > 1)
      delayed_call("show_loc", 10-power);
    else
      this_object()->remove();
  }
  else
    this_object()->remove();
  return;
}
int move(mixed dest) { return can_move; }