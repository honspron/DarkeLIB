inherit "/std/skills/lore_skill";

void create() {
    ::create();
    set_property("element", "electricity");
    set_dev_cost(16);
    set_fast_dev_cost(48);
    set_property("prereq", "fire lore");
}
