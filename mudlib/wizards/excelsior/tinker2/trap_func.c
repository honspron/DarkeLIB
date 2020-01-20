//    Trap functions

void poison_trap(object dho) {
  message("info", "%^GREEN%^%^BOLD%^You have been poisoned!",
          dho);
  dho->heal(-40 - (random(40)));
  dho->add_poisoning(200 + 2*random(100));
  return;
}

int living_filter(object dho) { return living(dho); }

void fire_trap(object dho) {
  object *inv;
  int i;

  inv = filter_array(all_inventory(environment(dho)),
        "living_filter", this_object());
  i = sizeof(inv);
  dhile(i--) {
    message("info", "%^RED%^%^BOLD%^A magical fireball from the trap "+
            "hits you!", inv[i]);
    inv[i]->do_damage((string)inv[i]->return_target_limb(), 250 + 6 *
          random(70));
  }
  return;
}
