inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","blessing of knowledge");
    set_property("skill","prayer");
    set_property("casting time",5);
    set_property("base mp cost",25);
    set_property("dev cost", 30);
    set_property("fast dev cost", 75);
    set_property("spell level", 4);
    set_property("moon","ankh");
    set_property("caster message","You pray for a blessing of knowledge for $T.");
    set_property("target message","$C prays for a blessing of knowledge for you.");
    set_property("observer message","$C appears to pray for $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "4D6");
    set_property("stats", ({ "intelligence", "wisdom", "charisma" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 360);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",@TEXT
This spell gives a general short-term bonus in skills and stats which
may be useful in a variety of situations.  Blessings are stackable.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if((int)at->query_bless_num() >= 2) {
    message("info", (string)at->query_cap_name() +
    " cannot receive additional blessings of knowledge.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/luck_shadow");
  ob->set_luck(random(power*2)+((int)caster->query_level()/3));
  ob->start_shadow(at, props["duration"],
		   "%^CYAN%^A bless of knowledge wears off.");
  ::spell_func(caster, at, power, args, flag);
  return;
}
