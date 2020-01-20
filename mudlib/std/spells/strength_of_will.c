inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","strength of will");
    set_property("skill","prayer");
    set_property("casting time",18);
    set_property("base mp cost",75);
    set_property("dev cost", 144);
    set_property("fast dev cost", 323);
    set_property("spell level", 10);
    set_property("moon","ankh");
    set_property("caster message","You empower $T with strength of will.");
    set_property("target message","$C empowers you with strength of will.");
    set_property("observer message","$C appears to pray for $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "2D6");
    set_property("stats", ({ "wisdom" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 75);
    return;
}

int res_spell() { return 1; } 

void info() {
message("help",@TEXT
This spell grants the target special Willpower which will aid them to resist spells cast upon them.  Strength of Will is not stackable.
TEXT
,this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob;

  seteuid(getuid());
  if((int)at->query_resist_num() >= 1) {
    message("info", (string)at->query_cap_name() +
            " already has the maximum number of strength of will spells on "+
            objective(at) + ".", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  ob = new("/std/spells/shadows/mag_resist_shad");
  ob->set_resist(random(power*5) + power*5);
  ob->start_shadow(at, props["duration"],
                   "%^YELLOW%^Your feel your extra willpower slowly fade away.");
  ::spell_func(caster, at, power, args, flag);
  return;
}
