inherit "/std/skills/lore_skill";

void create() {
    ::create();
    set_property("element", "inertia");
    set_dev_cost(15);
    set_fast_dev_cost(45);
}
