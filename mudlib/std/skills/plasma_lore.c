inherit "/std/skills/lore_skill";

void create() {
    ::create();
    set_property("element", "plasma");
    set_dev_cost(31);
    set_fast_dev_cost(90);
    set_property("prereq", "electricity lore");
}
