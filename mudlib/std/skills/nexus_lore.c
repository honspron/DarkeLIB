inherit "/std/skills/lore_skill";

void create() {
    ::create();
    set_property("element", "nexus");
    set_dev_cost(58);
    set_fast_dev_cost(190);
    set_property("prereq", "aether lore");
}
