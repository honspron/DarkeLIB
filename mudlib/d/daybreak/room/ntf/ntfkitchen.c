#include <std.h>
inherit ROOM;

void init() {
    ::init();
    add_action("donate", "drop");
}

void create() {
    ::create();
    set_property("light", 5);
    set_property("indoors", 1);
    set("short", "A small soup kitchen.");
    set("long", "This is a small soup kitchen provided and sponsored by the
NTF, the Needy Thieves Foundation. This kitchen was placed here by the
foundation in the hopes of sustaining those less fortunate thieves
throughout the realms. Several meals a day are served to the less fortunate
through the graces of the NTF. A small cardboard sign is tacked to the
wall.\n");

	set_property("no attack", 1);
       add_exit("/d/daybreak/room/db_slum", "north");
        add_exit("/d/daybreak/room/ntf/line", "line");
        add_exit("/d/daybreak/room/ntf/shower", "shower");
        add_pre_exit_function("line","check_money");
        set_items(([
        "line" :
        "The soup line is filled with several needy thieves looking for a handout.",
        ({"kitchen","soup kitchen"}) :
        "This kitchen is sponsored by the graces of the NTF and the gods above!",
        "sign" : 
        "The sign says, Get in line you beggar! and points to the end of the line."
        ]));

        set_listen("default", "You hear the stomachs of the hungry, wretched and destitute thieves of the realms as they wait hungrily in line for a handout.\n");
        set_smell("default", "You smell the delicious aroma of a hot meal waiting for you at the end of the line!\n");
}

void reset() {
  object ob;
  if(!present("volunteer"))
  new("/d/daybreak/mon/ntfvolunteer")->move(this_object());
  if(!present("box")) {
    ob = new("/d/daybreak/obj/ntfbox");
    ob->set_key("ntf donation box key");
    ob->set_lock("locked");
    ob->set_lock_level(75);
    ob->set_trap_func("/wizards/diewarzau/obj/misc/trap_func", "gate_trap");
    ob->set_trap_level(60);
    ob->move(this_object());

}
}
int check_money() {
  int money;
  money = (int)this_player()->query_money("silver");
  if(money > 5000) {
write("An NTF volunteer steps in front of you as you try to enter the line,");
write("You are not necessarily what the council would deem as poor or needy. Come back when you are a little less Well-to-Do!");
    return 0;
}
    else return 1;
}
int donate(string str) {
   object ob;
   string a;
   int rew, div;
   if(!str) {
     notify_fail("drop what?\n");
        return 0;
}
   a = lower_case(str);
   ob = present(a, this_player());
   if(!ob) {
     notify_fail("drop what?\n");
        return 0;
}
   ob->remove();
   div = 0;
   if(this_player()->query("last drop")) {
     div = time() - (int)this_player()->query("last drop");
     div = 50/(div+1);
}
   if(div < 1) div = 1;
   this_player()->set("last drop", time());
   rew=(random(7)+random(7)+random(7)+random(7)+random(7))*2*(int)this_player()->query_level()/div;
   this_player()->add_exp(rew);
    write("A tyke no older than 5 runs up and hugs your leg tightly.");
    write("Thank you! she cries,");
    write("We are very hungry indeed!");
    write("We have not been able to find any victims in days!\n");
    write("You drop a " + a + ".");
    write("You receive "+rew+" experience as reward for your donation.\n");
        return 1;
}
