// Muerta Quest Item 1
// Created by Zortek
// 031596

inherit "/std/armour";

void create() {
    ::create();
    set_name("rusted helm");
    set("id", ({ "helm", "rusted helm", "mqc1" }) );
    set("short", "a rusted helm");
     set("long", "A old, rusted spindle top helm with a rotted lining.");
    set_weight(250);
    set_value(10);
    set_type("helmet");
    set_ac(1);
    set_limbs( ({ "head" }) );
}
