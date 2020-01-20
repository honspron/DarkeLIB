#include <std.h>

inherit MONSTER;

void create() {
  ::create();
    set_name("goff");
    set_id( ({ "goff", "mine builder" }) );
    set_short("Goff, the Mine Builder");
    set("race", "half-orc");
    set_long(
    "Goff is a muscular half-orc who looks like he has seen "
    "his share of manual labor in his life.");
    set_gender("male");
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
    set_skill("dodge", 60);
    set_skill("parry", 75);
    set_stats("dexterity", 90);
    set_skill("conjuration", 70);
    set_spell_level("ice dagger", 4);
    add_spell("ice dagger", "$A");
    set_combat_chance(80);
}
int query_num_rounds() { return 3; }

string query_element() { return "vacid"; }
