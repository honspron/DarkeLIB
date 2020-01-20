#include <std.h>
#include <move.h>
inherit LIVING;

string owner, caster, *chans;
int duration, can_move;

void init() {
  if((string)this_player()->query_true_name() == owner ||
     (string)this_player()->query_true_name() == caster ||
     archp(this_player()) ) {
    add_action("sever_me", "sever");
    add_action("no_drop", "drop");
    add_action("no_drop", "give");
  }
}
void create() {
  set_name("channel_ward");
  enable_commands();
  duration = 5;
  can_move = MOVE_OK;
}
void set_up(string cast, string own, int power, string *channels) {
  int x;
  string msg;
  caster = cast;
  owner = own;
  duration = 3+power * power * power;
  chans = channels;
  x = sizeof(chans);
  msg = " ";
  while(x--)
    msg += "["+chans[x]+"] ";
  if(owner)
    message("clairvoy","[###]:"+msg+": Ward Active", find_living(owner));
  "/daemon/chat"->add_user(chans);
  move_object(find_living(owner));
  can_move = MOVE_NOT_ALLOWED;
}
int sever_me(string str) {
  if(str != "channel ward") {
    notify_fail("Sever what?\n");
    return 0;
  }
  this_object()->remove();
  return 1;
}
void remove() {
  int x;
  string msg;
  can_move = MOVE_OK;
  if((!owner || !caster) && (!chans || chans == ({})) ) {
    ::remove();
    return;
  }
  x = sizeof(chans);
  msg = " ";
  while(x--)
    msg += "["+chans[x]+"] ";
  if(owner)
    message("clairvoy","[###]:"+msg+": Ward Severed", find_living(owner));
  "/daemon/chat"->remove_user(chans);
  ::remove();
}
void receive_message(string msg_class, string msg) {
  int x;
  object who;
  
  if(base_name(previous_object(1)) != "/daemon/chat") return;
  if(!who = find_living(owner)) this_object()->remove();
  if((string)who->query_class() != "seer") {
    who->do_damage("head",1);
    message("info","You feel a stabbing pain in your head.",who);
  }
  message("clairvoy", "###: : %^RESET%^"+msg, who );
  who->add_mp(1*sizeof(chans));
  x = who->query_mp();
  if(x < 0) {
    who->add_hp(x);
    who->add_mp(-x);
  }
  if(--duration < 1) {
    this_object()->remove();
  }
}
string query_cap_name() { return "Someone"; }
int move(mixed dest) { return can_move; }