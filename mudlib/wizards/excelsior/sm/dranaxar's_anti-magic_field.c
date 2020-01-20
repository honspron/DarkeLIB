inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","dranaxar's anti-magic field");
    set_property("skill","sorcery");
    set_property("casting time",15);
    set_property("base mp cost",78);
    set_property("dev cost", 105);
    set_property("fast dev cost", 288);
    set_property("spell level",20);
    set_property("moon","luna");
    set_property("caster message","You summon an anit-magic field.");
    set_property("target message","");
    set_property("observer message","$C summons an anti-magic field.");
    set_property("spell type",({ }));
    set_property("duration", 60);
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This is a highly imporved version of anti-magic aura (see 'help spell "
"anti-magic aura'), in that it only dampens the spellcasting of others.  "
"Those in your party are immune to the effects as well.",
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
  ob = new("/wizards/diewarzau/obj/misc/d_am_aura");
  ob->move(environment(caster));
  ob->set_level(power);
  ob->set_caster(caster);
  ob->set_duration(props["duration"]);
  remove();
  return;
}
