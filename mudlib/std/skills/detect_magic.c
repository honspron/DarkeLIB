inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("intelligence");
    set_dev_cost(19);
    set_fast_dev_cost(50);
}

void info() {
message("help",
"This skill allows passive detection of magical auras on objects.  They will "
"glow if they have enchantments.  Also, locked enchantments can be detected.  "
"You can list locked enchantments by typing 'help <item>' when you are "
"holding the item.",
this_player());
}

