#include <std.h>
inherit DAEMON;

int cmd_dragonraid(string str) {
	if(!archp(previous_object())) return 0;
}
void raid(object ob) {
::raid();
object ob1;
message("shout", "%^BOLD%^%^RED%^A tremendous roar is heard far off on the breeze.",
users());
ob1 = new("/wizards/traer/dragon");
   ob1->set_moving(1);
   ob1->set_speed(10);
   ob1->move(find_object_or_load("/d/daybreak/room/dbns1"));
}
