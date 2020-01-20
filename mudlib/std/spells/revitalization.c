inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","revitalization");
    set_property("skill","woodland lore");
    set_property("casting time",6);
   set_property("base mp cost",10);
    set_property("dev cost", 76);
    set_property("fast dev cost", 250);
    set_property("spell level", 15);
    set_property("moon","ankh");
    set_property("caster message","You cast a revitalization spell upon $T.");
    set_property("target message","$C casts a revitalization spell upon you.");
    set_property("observer message","$C casts a revitalization spell upon $T.");
    set_property("spell type",({  }));
    set_property("must be present",1);
    set_property("target type", "living");
    return;
}

void info() {
message("help",
"This is a very powerful healing spell.  "
"It restores 1/6 of the target's lost hp per level of the spell, meaning "
"that at level *6, all hp are restored.  The mp cost of the spell is "
"10 mp per level plus 1 mp for every 2 hp restored.  If you do not "
"have sufficient mp, the max amount is used.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  int mult, hp, mp_cost;

  hp = (int)at->query_max_hp() - (int)at->query_hp();
  hp = hp * power / 6;
  if(hp > (int)caster->query_mp() * 2)
    hp = (int)caster->query_mp() * 2;
  mp_cost = hp/2;
  if(flag)
    mult = -1;
  else mult = 1;
  at->add_hp(mult*hp);
  caster->add_mp(-1*mp_cost);
  remove();
  return;
}
