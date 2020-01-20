inherit "/std/spells/spell";
inherit "/std/spells/weapon_stack_logic";

void create() {
    ::create();
    set_property("name","demon lord sword");
    set_property("skill","chaos magic");
    set_property("stack key", "demon sword");
    set_property("stack num", 2);
    set_property("casting time",12);
    set_property("base mp cost",66);
    set_property("dev cost",144);
    set_property("fast dev cost",430);
    set_property("spell level", 28);
    set_property("moon","warzau");
    set_property("damage multiplier", 1);
    set_property("caster message","You cast demon sword at $T.");
    set_property("target message","");
    set_property("observer message","$C casts demon sword at $T.");
    set_property("spell type",({}));
    set_property("duration", 720);
    set_property("must be present", 1);
    set_property("target type", "living");
    set_property("prereq", "greater demon sword");
    return;
}

void info() {
message("help",
"This spell binds a demon lord to your weapon, increasing damage.  "
"This spell must be cast at a lesser demon which has been summoned and controlled "
"by you.\n"
"Syntax: cast *<pow> demon lord sword at <demon> with <weapon>\n"
"Ex: cast *2 demon lord sword at lesser demon with longsword\n",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, weap;
  
  if(!at->id("demon lord")) {
    message("info", "You must cast this spell at a demon lord.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!at->query_owner() || (string)at->query_owner() != (string)caster->query_name()) {
    message("info", "The demon must have been summoned and contolled by you.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "Instead of binding the demon to your weapon, you release it "
      "from your control and it attacks!", caster);
    message("info", (string)at->query_cap_name() + " angrily attacks "+
          (string)caster->query_cap_name() + "!", environment(caster),
          ({ caster, at }));
    at->set_owner("asskicker");
    at->kill_ob(caster, 0);
    remove();
    return;
  }
  if((int)at->query_power() < power) {
    message("info", "The demon must be equal or greater power than the spell.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  if(!args || !(weap = present(lower_case(args), caster))) {
    if(!args)
      message("info", "You must supply a weapon to which to bind the demon.",
          caster);
    else
      message("info", "You have no '"+args+"'.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->remove();
  message("info", "You bind the demon to "+(string)weap->query_short()+".", caster);
  ob = new("/std/spells/shadows/weapon_shadow");
  if(!check_stack(weap, ob)) {
    message("info", "You may not stack any further demons on that weapon.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob->set_extra_wc(([ "impact" : 13*power ]));
  ob->set_extra_wc(([ "disruption" : 10*power ]));
  ob->set_auto_crits(([ "disruption D" : 2*power ]));
  ob->start_shadow(weap, props["duration"], "%^CYAN%^A demon sword spell wears off.");
  remove();
  at->remove();
  return;
}











