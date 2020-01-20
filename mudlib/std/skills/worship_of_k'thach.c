inherit "/std/skills/skill.c";

void create() {
    ::create();
    set_stat("wisdom");
    set_dev_cost(10);
    set_fast_dev_cost(35);
}

void info() {
message("help",
"This is a special skill with the religious rites demanded by the deity "
"K'thach, who watches over the war-priests.",
this_player());
}

