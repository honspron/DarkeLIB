#include <std.h>

inherit MONSTER;

create() {
  ::create();
    set_name("kohr amaz");
    set_id( ({ "kohr", "clan registrar", "kohr amaz" }) );
    set_short("Kohr Amaz, the Clan Registrar");
    set("race", "high-man");
    set_long(
    "Sansef is a tall, imposing high-man with a scraggly beard.  "
    "He grunts as you walk in.");
    set_body_type("human");
    set_level(14);
    set_property("melee damage", ([ "crushing" : 30]));
    set_skill("melee", 85);
    set_skill("dodge", 60);
    set_skill("parry", 75);
    set_stats("dexterity", 90);
    set_skill("conjuration", 80);
    set_spell_level("lightning bolt", 5);
    add_spell("lightning bolt", "$A");
    set_combat_chance(100);
}
