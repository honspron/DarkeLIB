#include <std.h>
#include <rooms.h>

inherit OBJECT;

int strength;
int intox;
int drinks_left;


int full() { return drinks_left; }

void create() {
  ::create();
  strength = -1;
  intox = 0;
  set_id( ({ "bottle", "blessed bottle", "blessed wine bottle" }) );
  set_name("blessed wine bottle");
  set_long(@TEXT
This is a hand-blown glass bottle with a gem encrusted silver 
stopper on top which may be used to contain water, wine, or the like.
It bears the Papal Seal of the Holy Church and may be used to carry
blessed fluids.
TEXT
);
  set_weight(45);
  set_value(350);
  return;
}

string query_short() {
  if(strength) {
    switch(drinks_left) {
    case 14..15:
      return "Blessed wine bottle (full)";
    case 4..13:
      return "Blessed wine bottle (semi-full)";
    case 1..3:
      return "Blessed wine bottle (almost empty)";
    default:
      return "Blessed wine bottle (empty)";
    }
  }
  else return "Blessed wine bottle (empty)";
}

void fill(string id, int drink, int alc) {
  set_id(query_id() + ({ id }));
  strength = drink;
  intox = alc;
  set_value(375+alc);
  drinks_left = 15;
  return;
}

void empty() {
  drinks_left = 0;
  set_value(200);
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
  write("You drink the contents of the bottle....aaaaahh.");
  this_player()->add_quenched(strength);
  this_player()->add_intox(intox);
  this_player()->add_mp(intox/10);
  drinks_left--;
  set_value(query_value()-20);
  if(drinks_left <= 0)
    this_object()->empty();
  return 1;
}



