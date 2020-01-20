inherit "/std/skills/skill";

void create() {
    ::create();
    set_dev_cost(11);
    set_fast_dev_cost(30);
    set_stat("intelligence");
}

void info() {
message("help","This skill reduces the cost of telepathic tells and shouts "
"which are normally very costly in terms of mp.  Tells and shouts are "
"particularly useful, because everyone understands them, regardless of "
"languages known.", this_player());
}
