// Wizard:  Khojem
// blessed waterskin
// waterskin.c
// Modified by Nevin for the cleric shop

#include <std.h>;

inherit OBJECT;

int strength;
int intox;
int drinks_left;

int full() { return drinks_left; }

void create() {
  :: create();
  strength = 0;
  drinks_left = 0;
  intox = 0;
  set_id(({ "water", "skin", "waterskin", "water skin", "blessed waterskin", "blessed water skin" }));
  set_name("blessed waterskin");
	set("long",
		"This skin bag has a spigot which may be used for containing "
		"water, wine, or the like.  It bears the Papal Seal of the "
		"Holy Church and may be used to carry blessed fluids."
	);
  set_weight(12);
  set_value(80);
  return;
}

string query_short() {
  switch(drinks_left) {
    case  10   : return "blessed waterskin is (full)";
    case 7..9  : return "blessed waterskin is (mostly full)";
    case 4..6  : return "blessed waterskin is (semi-full)";
    case 1..3  : return "blessed waterskin is (nearly empty)";
    default    : return "blessed waterskin is (empty)";
  }
}

void fill(string id, int drink, int alc) {
  strength  = drink;
  intox     = alc;
  set_value(100+alc);
  drinks_left = 10;
  say(this_player()->query_cap_name()+" fills a blessed waterskin.\n");
  return;
}

void empty() {
  set_value(80);
  drinks_left = 0;
  strength    = 0;
  intox       = 0;
  return;
}

void init() {
  :: init();
  add_action("drink_me","drink");
  add_action("pour_me", "pour");
  add_action("pour_me", "empty");
  return;
}

int pour_me(string str) {
  if(present(str,this_player()) != this_object()) return 0;
  if(drinks_left == 0) return 0;
  write("You empty the contents of a blessed waterskin.\n");
  say(this_player()->query_cap_name()+" empties a blessed waterskin.\n");
  this_object()->empty();
  return 1;
}

int drink_me(string str) {
  if(present(str,this_player()) != this_object()) return 0;
  if(drinks_left < 1) {
    write("Hmmm...   it is empty.\n");
    return 1;
  }
  write("You chug the contents of the waterskin.\n");
  say(this_player()->query_cap_name()+" drinks from a blessed waterskin.\n");
  this_player()->add_quenched(strength);
  this_player()->add_intox(intox);
  this_player()->add_mp(intox/10);
  drinks_left--;
  if(drinks_left > 0)
    set_weight(12 + (4 * drinks_left));
  else
    this_object()->empty();
  return 1;
}
  
