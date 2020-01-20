//    Poison Rune
inherit "/wizards/diewarzau/obj/misc/rune";

void create() {
  ::create();
  set_id(({ "rune", "summon rune", "summoning rune" }));
  set_short("%^RESET%^%^GREEN%^%^BOLD%^A summoning rune%^RESET%^%^MAGENTA%^%^BOLD%^");
  set_long("This rune is inscribed on the floor in an ancient magical language.");
  set("function", (: this_object(), "do_gate" :));
  return;
}

void do_gate(object who) {
  object ob;

  seteuid(getuid());
  if(who->is_pet()) return;
  ob = new("/wizards/diewarzau/obj/pet/greater_demon");
  ob->set_owner("asskicker");
  ob->set_up(query_level());
  ob->set_dur(query_level() * 60);
  message("info", "%^GREEN%^%^BOLD%^A Greater Demon appears!",
    environment(who));
  ob->move(environment(who));
  if(random(100) >= ((int)who->query_skill("control demon")-15*query_level())) {
    ob->kill_ob(who, 0);
    message("info", "%^RED%^%^BOLD%^The Demon attacks "+
      (string)who->query_cap_name()+"!", environment(who), ({ who }));
    message("info", "%^RED%^%^BOLD%^The Demon attacks you!", who);
    if(random(100) < 11*query_level()) {
      ob->set_following(who);
      who->add_follower(ob);
    }
  } else {
    message("info", "You have controlled the demon.  It does not attack.",
        who);
  }
  return;
}

