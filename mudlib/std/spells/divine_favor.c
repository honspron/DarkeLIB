inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","divine favor");
    set_property("skill","prayer");
    set_property("casting time",18);
    set_property("base mp cost",75);
    set_property("dev cost", 144);
    set_property("fast dev cost", 323);
    set_property("spell level", 24);
    set_property("moon","ankh");
    set_property("caster message","You pray for divine favor on $T.");
    set_property("target message","$C prays for divine favor on you.");
    set_property("observer message","$C appears to pray for $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "2D6");
    set_property("stats", ({ "charisma" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 75);
    set_property("prereq", "divine transformation");
    return;
}

int res_spell() { return 1; }

void info() {
message("help",@TEXT
This spell grants the target special Divine Favor which will aid the
player in any given situation.  Divine Favors are not stackable.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if((int)at->query_favor_num() >= 1) {
    message("info", (string)at->query_cap_name() +
	    " already has the maximum number of divine favor spells on "+
	    objective(at) + ".", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/luck_shadow2");
  ob->set_luck(random(power*5) + power*5);
  ob->start_shadow(at, props["duration"],
		   "%^CYAN%^A divine favor spell wears off.");
  ::spell_func(caster, at, power, args, flag);
  return;
}
