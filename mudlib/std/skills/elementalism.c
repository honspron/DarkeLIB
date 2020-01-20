inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(18);
    set_fast_dev_cost(61);
}

void info() {
message("help",
"This is the principle spell casting skill of the elementalist, and it "+
"allows him or her to cast the wide variety of powerful elemental spells.  "+
"Note however that it is useless without elemental lore skills (e.g., "+
"fire lore, earth lore, plasma lore, aether lore, etc.)",
this_player());
}

