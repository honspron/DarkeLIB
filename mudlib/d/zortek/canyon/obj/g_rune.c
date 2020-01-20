//    Poison Rune
inherit "/wizards/diewarzau/obj/misc/rune";

void create() {
  ::create();
  set_id(({ "gate rune", "rune" }));
  set_short("%^RESET%^%^BLUE%^%^BOLD%^A gate rune%^RESET%^%^MAGENTA%^%^BOLD%^");
  set_long("This rune is inscribed on the floor in an ancient magical language.");
  set("function", (: this_object(), "do_gate" :));
  return;
}

void do_gate(object who) {
  who->move_player("/wizards/diewarzau/rooms/warp", 0);
  return;
}

