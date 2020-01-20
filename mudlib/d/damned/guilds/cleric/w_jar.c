#include <std.h>

inherit OBJECT;

int strength;
int intox;
int drinks_left;


int full() { return drinks_left; }

void create() {
  ::create();
  strength = -1;
  intox = 0;
  set_id( ({ "mason jar", "jar", "blessed jar", "blessed mason jar" }) );
  set_name("blessed mason jar");
  set_long(@TEXT
This is a ceramic jar that is used to store preserves, pickles, or
any of many foodstuffs.  This particular jar bears the Papal seal of
the Holy Church and may be used to contain blessed liquids.
TEXT
);
  set_weight(55);
  set_value(25);
  return;
}

string query_short() {
  if(strength) {
    switch(drinks_left) {
    case 3:
      return "Blessed mason jar (full)";
    case 2:
      return "Blessed mason jar (semi-full)";
    case 1:
      return "Blessed mason jar (almost empty)";
    default:
      return "Blessed mason jar (empty)";
    }
  }
  else return "Blessed Mason Jar (empty)";
}

void fill(string id, int drink, int alc) {
  set_id(query_id() + ({ id }));
  strength = drink;
  intox = alc;
  set_value(35+alc);
  drinks_left = 3;
  return;
}

void empty() {
  set_id(({ "jar", "mason jar" }) );
  //IF it was blessed, it isn't anymore...
  set_name("jar");
  set_value(9);
  strength = 0;
  intox = 0;
  return;
}

void init() {
  ::init();
  add_action("drink_me", "drink");
  return;
}

int drink_me(string str) {
  if(present(str, this_player()) != this_object()) return 0;
  if(strength < 1) {
    write("It is empty.");
    return 1;
  }
  write("You drink the contents of the mason jar....aaaaahh.");
  this_player()->add_quenched(strength);
  this_player()->add_intox(intox);
  this_player()->add_mp(intox/10);
  drinks_left--;
  if(drinks_left <= 0)
    this_object()->empty();
  return 1;
}
