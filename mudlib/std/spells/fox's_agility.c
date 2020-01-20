#define SKILLS_AFFECTED ([ "attack" : 4, "blade" : 3, "two handed staff" : 3, "axe" : 3, "knife" : 3, "dodge" : 2, "parry" : 2, "offhand training" : 3,"thrown" : 3, "repair weapon" : 4 ])
    
inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","fox's agility");
    set_property("skill","woodland lore");
    set_property("casting time",7);
    set_property("base mp cost",30);
    set_property("dev cost", 25);
    set_property("fast dev cost", 95);
    set_property("spell level", 7);
    set_property("moon","ankh");
    set_property("caster message","You call upon the fox's agility to help $T.");
    set_property("target message","$C calls upon the fox's agility to help you.");
    set_property("observer message","$C calls upon the fox's agility to help $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "1D12");
    set_property("stats", ({ "dexterity" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 160);
    return;
}

int res_spell() { return 1; }

void info() {
message("help",@TEXT
This spell gives a general short-term bonus in skills and stats which
may be useful in a variety of situations.  Each spell is stackable 2 times.
Most general physical skills will receive bonuses from this spell.
Skills used to accomplish unholy pursuits (back stab, steal, etc.) will
not be affected.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
//  object ob;
  mapping sk_aff = SKILLS_AFFECTED;

  seteuid(getuid());
  if ((int)at->query("a bless num") >= 2) {
    message("info", (string)at->query_cap_name() +
            " can receive no fox's agility spells.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) message("info", "The spell's effects are reversed!", caster);
  map_mapping(sk_aff, (: call_other($3, $4, $1, $2 * $5) :),
    at, "add_skill_bonus", ((flag)?-1:1) * power);
  at->set("a bless num", (int)at->query("a bless num") + 1);
  delayed_call("remove_spell", props["duration"], power, at, flag);
  ::spell_func(caster, at, power, args, flag);
  return;
}

void remove_spell(int power, object at, int flag) {
  mapping sk_aff = SKILLS_AFFECTED;
  
  if(!at) {
    remove();
    return;
  }
  message("info", "You don't feel quite as agile.", at);
  map_mapping(sk_aff, (: call_other($3, $4, $1, $2 * $5) :),
    at, "add_skill_bonus", ((flag)?1:-1) * power);
  at->set("a bless num", (int)at->query("a bless num") - 1);
  remove();
  return;
}
