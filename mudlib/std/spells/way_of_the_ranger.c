inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","way of the ranger");
    set_property("skill","woodland lore");
    set_property("casting time",35);
    set_property("base mp cost",135);
    set_property("dev cost", 95);
    set_property("fast dev cost", 281);
    set_property("spell level", 19);
    set_property("moon","luna");
    set_property("caster message","You show $T the way of the Ranger.");
    set_property("target message","$C shows you the way of the Ranger.");
    set_property("observer message","$C shows $T the way of the Ranger.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    set_property("duration", 60);
    return;
}

void info() {
message("help",
"An extremely powerful spell, holy mission allows the recipient to fight "
"WITHOUT TAKING ANY DAMAGE for the duration of the spell.  When the spell "
"expires, however, the recipient takes ALL cumulative damage he/she would "
"have taken during the course of the spell.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object ob, ob2;

  if(at->query_mission()) {
    message("info", (string)at->query_cap_name() +" already knows the way of the Ranger.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  ob = new("/std/spells/shadows/wor_shad");
  ob2 = new("/d/damned/guilds/ranger/wor_ob");
  ob2->move(at);
  ob->set_mission_ob(ob2);
  ob->start_shadow(at, props["duration"],"%^RED%^%^BOLD%^The Way of the Ranger ends, and you take all your "+ "wounds upon you.");
  if(flag) {
    message("info", "%^RED%^%^BOLD%^Somehow, you think you misdirected the energies of "+
            "your spell.", caster);
    message("info", (string)caster->query_cap_name() + 
            " looks puzzled.", environment(caster), ({ caster }));
    ob->set_fumble(1);
  }
  remove();
  return;
}
