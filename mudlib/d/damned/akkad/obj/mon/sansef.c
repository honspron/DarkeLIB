#include <std.h>

inherit MONSTER;

create() {
  ::create();
    set_name("sansef");
    set_id( ({ "sansef", "castle salesman" }) );
    set_short("Sansef, the Castle Salseman");
    set("race", "dwarf");
    set_long(
    "Sansef is a squat dwarf with a bushy black beard.  "
    "He gives you a warm smile.");
    set_body_type("human");
    set_level(14);
    set_hp(200000);
   set_property("enhance criticals", -10);
    set_max_hp(200000);
    set_property("melee damage", ([ "crushing" : 99]));
    set_skill("melee", 185);
    set_skill("elementalism", 175);
    set_spell_level("elemental storm", 6);
    add_spell("elemental storm", "");
    set_combat_chance(80);
    set_skill("dodge", 60);
    set_skill("parry", 75);
    set_stats("dexterity", 90);
    set_skill("conjuration", 70);
    set_combat_chance(80);
}
int query_num_rounds() { return 3; }

string query_element() { return "vacid"; }
