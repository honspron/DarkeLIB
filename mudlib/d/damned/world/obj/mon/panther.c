#include <std.h>

inherit MONSTER;

create() {
  ::create();
    set_name("panther");
    set_id( ({ "panther" }) );
    set_short("A black, ferocious panther");
     set("race", "panther");
    set_long("This panther doesn't look like he wants to be messed with.");
    set("aggressive", 1);
    set_body_type("quadruped");
    set_level(7);
    set_stats("intelligence", 20);
    set_property("melee damage", ([ "cutting" : 30]));
    set_skill("melee", 60);
    set_skill("dodge", 70);
    set_skill("parry", 20);
    set_stats("dexterity", 90);
    set_max_hp(400);
    set_hp(400);
    set_speed(60);
    set_moving(1);
}
