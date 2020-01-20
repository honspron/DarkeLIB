inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","poison rune");
    set_property("skill","enchantment");
    set_property("casting time",14);
    set_property("base mp cost",28);
    set_property("dev cost", 16);
    set_property("fast dev cost", 47);
    set_property("spell level", 3);
    set_property("moon","warzau");
    set_property("caster message","You inscribe a %^GREEN%^poison rune%^RESET%^ on the floor.");
    set_property("target message","");
    set_property("observer message","$C inscribes a %^GREEN%^poison rune%^RESET%^ on the floor.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 122);
    return;
}

void info() {
message("help",
"This spell inscribes a magical rune on the floor.  "
"Whenever someone (besides you) enters the room, the rune will affect "
"them.  This rune will poison any victims.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, *inv;
  int i, tot;

  seteuid(getuid());
  ob = new("/std/diewarzau/obj/misc/p_rune");
  ob->set("safe flag", 1);
  ob->move(environment(caster));
  ob->set_property("can resist", 1);
  ob->set_property("save mod", "constitution");
  ob->set_dur(props["duration"]);
  ob->set("safe flag", 0);
  ob->set_level(power);
  ob->set_caster_level((int)caster->query_level());
  if(flag) {
    message("info", "%^GREEN%^A poison rune goes off!", environment(caster));
    ob->set_caster("asskicker");
    ob->delay_action();
    remove();
    return;
  }
  inv = all_inventory(environment(caster));
  i = sizeof(inv);
  tot = 0;
  while(i--) tot += (int)ob->my_rune_filter(inv[i]);
  if(tot > 3) {
    message("info", "Only three poison runes may be in any room.", caster);
    ob->remove();
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob->set_caster((string)caster->query_name());
  remove();
  return;
}
