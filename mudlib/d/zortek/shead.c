#include <std.h>

inherit OBJECT;

void create() {
    seteuid(getuid());
    ::create();
    set_name("Silon's Head");
    set_id( ({ "head", "silon's head" }) );
    set_short("the head of Silon");
    set_long("This is the head of Silon.  It looks as though you "
      "could \"throw head at\" something, or maybe even \"mold head.\"");
    set_weight(0);
    set_value(0);
    set_property("no sell", 1);
}

void init() {
    ::init();
    add_action("throw_head", "throw");
    add_action("mold_head", "mold");
}

int throw_head(string arg) {
    object ob;
    string tmp, str;

    if(!arg) {
	message("throw_syntax", syntax("throw OBJ at LIV"), this_player());
	return 1;
    }
    sscanf(arg, "head at %s", str);
    if(strlen(arg) < 9 || arg[0..7] != "head at ") {
	message("throw_syntax", syntax("throw OBJ at LIV"), this_player());
	return 1;
    }
    ob = find_player(str);
    if(!ob) {
	message("throw", str + ": not found.", this_player());
	return 1;
    }
    message("throw_send", "You throw " + this_object()->query_short() + " at " +
      ob->query_cap_name() + ".", this_player());
    message("throw_receive", this_player()->query_cap_name() + " throws " + this_object()->query_short() +
      " at you.", ob);
    switch(random(5)) {
    case 1: tmp = "hits splat on the face"; break;
    case 2: tmp = "hits scraping the shoulder"; break;
    case 3: tmp = "bumps into the stomach"; break;
    case 4: tmp = "misses entirely"; break;
    default: tmp = "blasts, hitting the knees"; break;
    }
    message("throw_send", "It " + tmp + "!", this_player());
    message("throw_receive", "It " + tmp + "!", ob);
    this_object()->move(ob);
    return 1;
}

int mold_head(string arg) {
    if(arg != "head") {
	write(syntax("mold OBJ"));
	return 1;
    }
    message("prompt", "Who's head do you want it to imitate? [Silon is default]: ",
      this_player());
    input_to("finish_mold");
    return 1;
}

int finish_mold(string arg) {
    if(!arg || arg == "") {
	message("mold", "You mold the head to imitate Silon's head.", this_player());
	this_object()->set_name("Silon's Head");
	this_object()->set_id( ({ "silon's head", "head" }) );
	this_object()->set_short("the head of Silon");
	this_object()->set_long("This is the head of Silon.  It looks as though you "
	  "could \"throw head at\" something, or maybe even \"mold head.\"");
	message("mold", this_player()->query_cap_name() + " molds the head to imitate " +
	  capitalize(arg) + "'s head.", environment(this_player()), ({ this_player() }) );
	return 1;
    }
    message("mold", "You mold the head to imitate " + capitalize(
	arg) + "'s head.", this_player());
    this_object()->set_name(capitalize(arg) + "'s Head");
    this_object()->set_id( ({ lower_case(arg) + "'s head", "head" }) );
    this_object()->set_short("the head of " + capitalize(arg));
    this_object()->set_long("This is the head of " + capitalize(arg) +
      ".  It looks as though you could \"throw head at\" something, or "
      "maybe even \"mold head.\"");
    message("mold", this_player()->query_cap_name() + " molds the head to imitate " +
      capitalize(arg) + "'s head.", environment(this_player()), ({ this_player() }) );
    return 1;
}
