inherit "/std/Object";

void init() {
  ::init();
  add_action("nice_try", "quit");
  return;
}

int nice_try(string null) {
  message("info", "%^YELLOW%^You may not quit while using the way of the ranger.",
          this_player());
  return 1;
}

void create(){
    ::create();
    set_property("no save", 1);
    return;
}
