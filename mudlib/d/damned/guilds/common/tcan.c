#include <move.h>
inherit "/std/bag_logic.c";

void init() {
    ::init();
    add_action("trash_fun", "trash");
}

void create() {
    ::create();
    set("name", "a trash can");
    set("id", ({ "trash", "can", "trash can" }));
    set("short", "trash can");
    set("long",
      "                        _\n"
      "  ____________________/   \\_____________________\n"
      " |\\____________________________________________/|\n"
      " \\_____________________________________________/\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |___|___|___|___|___|   |   |   |\n"
      "  |   |   |   |                   |   |   |   |\n"
      "  |   |   |   |     TRASH CAN     |   |   |   |\n"
      "  |   |   |   |   'trash' your    |   |   |   |\n"
      "  |   |   |   |       JUNK        |   |   |   |\n"
      "  |   |   |   |___________________|   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n"
      "  |   |   |   |   |   |   |   |   |   |   |   |\n");
    set_weight(10000);
    set("value", 0);
    set_max_internal_encumbrance(10000);
    set_possible_to_close(0);
}
int trash_fun(string str) {
    object ob;
    string a;
    int rew, div;
    if(!str) {
	notify_fail("trash what?\n");
	return 0;
    }
    a = lower_case(str);
    ob = present(a, this_player());
    if(!ob) {
	notify_fail("trash what?\n");
	return 0;
    }
    div = 0;
    if(this_player()->query("last trash")) {
	div = time() - (int)this_player()->query("last trash");
	div = 50/(div+1);
    }
    if(div < 1) div = 1;
    this_player()->set("last trash", time());
    rew = (random(7)+random(7)+random(7)+random(7)+random(7))*(int)this_player()->query_level()/div;
    if(strsrch(ob->query_short(), "key") != -1 ||
      strsrch(ob->query_short(), "Key") != -1) { } else
	this_player()->add_exp(rew);
    ob->remove();
    write("You receive "+rew+" experience as reward for your cleaniness.");
    write("You trash a " + a + ".");
    return 1;
}

int move(mixed dest) {
    if(objectp(dest) && living(dest) && !wizardp(dest)) return MOVE_NOT_ALLOWED;
    return ::move(dest);
}
