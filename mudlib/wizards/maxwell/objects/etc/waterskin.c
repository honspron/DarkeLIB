#include "/adm/include/std.h"

inherit OBJECT;

int strength;
int intox;
int drinks_left;


int full() { return strength; }

void create() {
  ::create();
  strength = -1;
  intox = 0;
  set_id( ({ "skin", "water skin", "waterskin", "blessed water skin" }) );
  set_name("blessed water skin");
  set_long(@TEXT
This is a skin bag with a spigot which may be used for containing
water, wine, or the like.  It bears the Papal Seal of the Holy
Church and may be used to carry blessed fluids.
TEXT
);
  set_weight(15);
  set_value(55);
  return;
}

string query_short() {
  if(strength) {
    switch(drinks_left) {
    case 6:
      return "Blessed waterskin (full)";
    case 2..5:
      return "Blessed waterskin (semi-full)";
    case 1:
      return "Blessed waterskin (almost empty)";
    default:
      return "Blessed waterskin (empty)";
    }
  }
  else return "Waterskin (empty)";
}

void fill(string id, int drink, int alc) {
  set_id(query_id() + ({ id }));
  strength = drink;
  intox = alc;
  set_value(61+alc);
  drinks_left = 6;
  return;
}

void empty() {
  set_id(({ "skin", "water skin", "waterskin", }) );
  //IF it was blessed, it isn't anymore...
  set_name("waterskin");
  set_weight(15);
  set_value(5);
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
  write("You drink the contents of the waterskin....aaaaahh.");
  this_player()->add_quenched(strength);
  this_player()->add_intox(intox);
  this_player()->add_mp(intox/10);
  drinks_left--;
  if(drinks_left <= 0)
    this_object()->empty();
  return 1;
}
