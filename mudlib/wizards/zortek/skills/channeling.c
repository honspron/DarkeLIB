inherit "/std/skills/skill";

void create() {
    ::create();
    set_dev_cost(12);
    set_fast_dev_cost(25);
    set_stat("wisdom");
}

void info() {
message("help",@TEXT
Channeling powers involve direct contact between two or more minds.
This also forms the basis for channeling into or from personal or
group "power pools."

Examples include mind reading, personality swapping, memory
affectations, and psychic attacks.
TEXT
, this_player());
}
