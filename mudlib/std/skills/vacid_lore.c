inherit "/std/skills/lore_skill";

void create() {
    ::create();
    set_property("element", "vacid");
    set_dev_cost(31);
    set_fast_dev_cost(90);
    set_property("prereq", "ice lore");
}
