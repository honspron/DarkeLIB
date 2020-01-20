//    Trap functions

void poison_trap(object who) {
  message("info", "%^GREEN%^%^BOLD%^You have been poisoned!",
          who);
  who->heal(-40 - (random(40)));
  who->add_poisoning(200 + 2*random(100));
  return;
}

int living_filter(object who) { return living(who); }

void fire_trap(object who) {
  object *inv;
  int i;

  inv = filter_array(all_inventory(environment(who)),
        "living_filter", this_object());
  i = sizeof(inv);
  while(i--) {
    message("info", "%^RED%^%^BOLD%^A magical fireball from the trap "+
            "hits you!", inv[i]);
    inv[i]->do_damage((string)inv[i]->return_target_limb(), 250 + 6 *
          random(70));
  }
  return;
}
