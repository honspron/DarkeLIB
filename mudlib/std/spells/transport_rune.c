inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","transport rune");
    set_property("skill","enchantment");
    set_property("casting time",21);
    set_property("base mp cost",57);
    set_property("dev cost", 76);
    set_property("fast dev cost", 225);
    set_property("spell level", 15);
    set_property("moon","warzau");
    set_property("caster message","You inscribe a %^YELLOW%^%^BOLD%^transport rune%^RESET%^ on the floor.");
    set_property("target message","");
    set_property("observer message","$C inscribes a %^YELLOW%^%^BOLD%^transport rune%^RESET%^ on the floor.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 122);
    set_property("prereq", "transport beacon");
    return;
}

void info() {
message("help",
"This spell inscribes a magical rune on the floor.  "
"Whenever someone enters the room, the rune will affect "
"them.  This rune will transport anyone stepping into the rune to the location "
"of the transport beacon (see 'help spell transport beacon').  You must "
"have the transport becon spell to cast this spell.  Since this rune has peaceful "
"uses, it WILL affect the caster.  In order to avoid this, the caster "
"must preserve the rune and use the 'runeadd' command.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, *inv;
  int i, tot;
  mapping tmp;

  seteuid(getuid());
  ob = new("/std/diewarzau/obj/misc/t_rune");
  ob->set("safe flag", 1);
  ob->move(environment(caster));
  ob->set("safe flag", 0);
  ob->set_property("can resist", 1);
  ob->set_level(power);
  ob->set_dur(props["duration"]);
  ob->set_caster_level((int)caster->query_level());
  if(flag) {
    message("info", "%^YELLOW%^%^BOLD%^A transport rune goes off!", environment(caster));
    ob->set_caster("asskicker");
    ob->set_property("room", "/std/diewarzau/rooms/warp");
    ob->delay_action();
    remove();
    return;
  }
  if(!(tmp = (mapping)caster->query("transport beacon"))) {
    message("info", "You must have a transport beacon somewhere on the "+
      "mud for this spell to work.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(tmp["power"] < power) {
    message("info", "The transport beacon must be of a power equal to "
      "or greater than the power of this spell.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  inv = all_inventory(environment(caster));
  i = sizeof(inv);
  tot = 0;
  while(i--) tot += (int)ob->my_rune_filter(inv[i]);
  if(tot > 1) {
    message("info", "Only one transport rune may be in any room.", caster);
    ob->remove();
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob->set_property("room", tmp["room"]);
  ob->set_caster((string)caster->query_name());
  remove();
  return;
}
