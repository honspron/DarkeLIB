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
  set_id( ({ "flask", "blessed flask" }) );
  set_name("blessed flask");
  set_long(@TEXT
This is a silver flask with a screw on top which may be used to
contain water, wine, or the like.  It bears the Papal Seal of the
Holy Church and may be used to carry blessed fluids.
TEXT
);
  set_weight(25);
  set_value(150);
  return;
}

string query_short() {
  if(strength) {
    switch(drinks_left) {
    case 5:
      return "Blessed flask (full)";
    case 2..4:
      return "Blessed flask (semi-full)";
    case 1:
      return "Blessed flask (almost empty)";
    default:
      return "Blessed flask (empty)";
    }
  }
  else return "Blessed flask (empty)";
}

void fill(string id, int drink, int alc) {
  set_id(query_id() + ({ id }));
  strength = drink;
  intox = alc;
  set_value(155+alc);
  drinks_left = 5;
  return;
}

void empty() {
  set_long(@TEXT
This is a silver flask with a screw on top which may be used to
contain water, wine, or the like.
TEXT
);
  set_value(55);
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
  write("You drink the contents of the flask....aaaaahh.");
  this_player()->add_quenched(strength);
  this_player()->add_intox(intox);
  this_player()->add_mp(intox/10);
  drinks_left--;
  if(drinks_left <= 0)
    this_object()->empty();
  return 1;
}
