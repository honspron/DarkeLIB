inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","battle fury");
    set_property("skill","worship of k'thach");
    set_property("casting time",7);
    set_property("base mp cost",35);
    set_property("dev cost", 61);
    set_property("fast dev cost", 180);
    set_property("spell level", 12);
    set_property("moon","warzau");
    set_property("caster message","You cast battle fury.");
    set_property("target message","");
    set_property("observer message","$C casts BATTLE FURY!");
    set_property("spell type",({ "stat mod", "skill mod" }));
    set_property("no target", 1);
    set_property("stats", ({ "strength" }));
    set_property("skills", ({ "attack", "melee" }));
    set_property("stat dice", "3D6");
    set_property("skill dice", "3D8");
    set_property("duration", 120);
    set_property("prereq", "battle aura");
    return;
}

void info() {
message("help",
"This spell grants the caster an additional attack in combat, as "
"well as increased strength and attack skill.  This spell cannot "
"be combined with haste.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(caster->query_haste()) {
    message("info", "A target may only receive one haste spell.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/haste_shadow");
  if(flag) {
    message("info", "You accidentally slow the target!",
      caster);
    ob->set_fumble();
  }
  ob->start_shadow(caster, props["duration"], "%^CYAN%^A haste spell expires.");
  ::spell_func(caster, caster, power, 0, 0);
  return;
}
