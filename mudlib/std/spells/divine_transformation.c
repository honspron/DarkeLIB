inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","divine transformation");
    set_property("skill","body alteration");
    set_property("casting time",9);
    set_property("base mp cost",68);
    set_property("dev cost", 48);
    set_property("fast dev cost", 130);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You cast divine transformation on $T.");
    set_property("target message","$C casts divine transformation on you.");
    set_property("observer message","$C casts a divine transformation on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "1D6");
    set_property("stats", ({ "strength", "intelligence", "dexterity" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 240);
    set_property("prereq", "blessing of agility");
    return;
}

int res_spell() { return 1; }

void info() {
message("help",
"This spell imbues the recipient with divine power, increasing stats, "
"allowing flight, and increasing bare-handed damage greatly.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if((int)at->query_d_trans()) {
    message("info", (string)at->query_cap_name() +
	    " has already been transformed.",
	    caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!flag) {
    ob = new("/std/spells/shadows/d_trans_shadow");
    ob->set_power(power);
    ob->start_shadow(at, props["duration"],
	  	   "%^CYAN%^Divine transformation wears off.");
  }
  ::spell_func(caster, at, power, args, flag);
  return;
}

