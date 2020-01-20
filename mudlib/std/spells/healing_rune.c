inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","healing rune");
    set_property("skill","enchantment");
    set_property("casting time",29);
    set_property("base mp cost",45);
    set_property("dev cost", 51);
    set_property("fast dev cost", 150);
    set_property("spell level", 10);
    set_property("moon","warzau");
    set_property("caster message","You inscribe a %^CYAN%^%^BOLD%^healing rune%^RESET%^ on the floor.");
    set_property("target message","");
    set_property("observer message","$C inscribes a %^CYAN%^%^BOLD%^healing rune%^RESET%^ on the floor.");
	set_property("spell type",({}));
    set_property("no target", 1);
    set_property("duration", 122);
    set_property("prereq", "exploding rune");
    return;
}

void info() {
message("help",
"This spell inscribes a magical rune on the floor.  "
"Whenever someone enters the room, the rune will affect "
"them.  This rune allows all in the room to heal at double rate (mp and hp).",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, *inv;
  int i, tot;

  seteuid(getuid());
  ob = new("/std/diewarzau/obj/misc/h_rune");
  ob->set("safe flag", 1);
  ob->move(environment(caster));
  ob->set("safe flag", 0);
  ob->set_dur(props["duration"]);
  ob->set_property("can resist", 1);
  ob->set_level(power);
  if(flag) {
    message("info", "%^BLUE%^%^BOLD%^A healing rune goes awry, damaging all in the room!", environment(caster));
    ob->set_caster("asskicker");
    inv = all_inventory(environment(caster));
    i = sizeof(inv);
    while(i--) {
      if(!living(inv[i])) continue;
      inv[i]->add_hp(-1 * (int)inv[i]->query_hp() / 2);
    }
    ob->remove();
    remove();
    return;
  }
  inv = all_inventory(environment(caster));
  i = sizeof(inv);
  tot = 0;
  while(i--) tot += (int)ob->my_rune_filter(inv[i]);
  if(tot > 3) {
    message("info", "Only three healing runes may be in any room.", caster);
    ob->remove();
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob->set_caster((string)caster->query_name());
  remove();
  return;
}
