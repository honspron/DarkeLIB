inherit "/std/skills/lore_skill";

void create() {
    ::create();
    set_property("element", "wind");
    set_dev_cost(10);
    set_fast_dev_cost(30);
    set_property("prereq", "air lore");
}
