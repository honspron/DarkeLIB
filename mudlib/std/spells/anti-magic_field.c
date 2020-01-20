inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","anti-magic aura");
    set_property("skill","sorcery");
    set_property("casting time",15);
    set_property("base mp cost",49);
    set_property("dev cost", 62);
    set_property("fast dev cost", 165);
    set_property("spell level", 14);
    set_property("moon","luna");
    set_property("caster message","You summon an anit-magic aura.");
    set_property("target message","");
    set_property("observer message","$C summons an anti-magic aura.");
    set_property("spell type",({ }));
    set_property("duration", 60);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This spell summons an aura about the room that dampens all spell "
"casting, INCLUDING your own.  Some spells may get through though, "
"particularly powerful ones, though casting the aura at a high power "
"level helps combat this effect.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "%^RED%^%^BOLD%^OOPS!  You misdirect the energies of your spell, "
            "robbing yourself of all magic points!", caster);
    message("info", (string)caster->query_cap_name()+" looks weaker.", environment(caster),
        ({ caster }));
    caster->add_mp( -1 * (int)caster->query_mp());
    remove();
    return;
  }
  if(present("anti-magic aura", environment(caster))) {
    message("info", "There is already an anti-magic aura around this room.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/wizards/diewarzau/obj/misc/am_aura");
  ob->move(environment(caster));
  ob->set_level(power);
  ob->set_duration(props["duration"]);
  remove();
  return;
}
