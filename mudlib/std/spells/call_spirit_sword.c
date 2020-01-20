inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","call spirit sword");
    set_property("skill","worship of k'thach");
    set_property("casting time",10);
    set_property("base mp cost",25);
    set_property("dev cost", 26);
    set_property("fast dev cost", 72);
    set_property("spell level", 5);
    set_property("moon","luna");
    set_property("caster message","You call the Sword of the Spirit to your hands.");
    set_property("target message","");
    set_property("observer message","$C calls the Sword of the Spirit into creation.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 600);
    set_property("prereq", "call divine plate");
    return;
}

void info() {
message("help",
"This spell summons the Sword of the Spirit into your possession.  The sword "
"is imbued with holy power.  In addition, the spell provides you "
"with the necessary skill to use the weapon as well!  Your skill "
"with the sword depends mainly on the power of the spell, "
"but also slightly on blade skill.\n"
"NOTE: If you unwield the weapon, it will disappear.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob, ob2, *weps;
  string *limbs;

  if(flag) {
    message("info", "The fumble causes you to be drained of "
      "half of your remaining mp!", caster);
    caster->add_mp(-1 * (int)caster->query_mp() / 2);
    remove();
    return;
  }
  weps = map_array((string *)caster->query_wielding_limbs(),
    (: call_other($2, $3, $1) :), caster, "query_weapon");
  weps = filter_array(weps, (: objectp :));
  if(weps && sizeof(weps)) {
    message("info", "In order to cast this spell, you must be "
      "wielding no weapons.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/wizards/diewarzau/obj/weapons/spirit_sword");
  ob->move(caster);
  limbs = (string *)caster->query_wielding_limbs();
  if(sizeof(limbs) < 1) {
    message("info", "You must have 1 wielding limb to cast this "
      "spell.", caster);
    caster->add_mp(props["mp cost"]);
    ob->remove();
    remove();
    return;
  }
  if(!caster->query_property("ambidextry") &&
    caster->query_property("handedness") &&
    (member_array((string)caster->query_property("handedness"),
    limbs) > -1)) {
    caster->force_me("wield sword of spirit in "+
      (string)caster->query_property("handedness"));
  }
  else caster->force_me("wield sword of spirit in "+
      limbs[0]);
  ob->set_dur(props["duration"]);
  ob->set_property("enchantment", 4*power);
  ob2 = new("/std/spells/shadows/skill_shadow");
  ob2->add_skill("holy", 40+6*power);
  ob2->add_new_skill_bonus("holy",
    (int)caster->query_skill("blade") / 3);
  ob2->start_shadow(caster, props["duration"]+30, 0);
  ob->set_shadow(ob2);
  remove();
  return;
}
