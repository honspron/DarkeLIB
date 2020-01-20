inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","demonic rebirth");
    set_property("skill","chaos magic");
    set_property("casting time",60);
    set_property("base mp cost",170);
    set_property("dev cost",81);
    set_property("fast dev cost",250);
    set_property("spell level", 19);
    set_property("moon","warzau");
    set_property("caster message","You cast demonic rebirth at $T.");
    set_property("target message","");
    set_property("observer message","$C casts demonic rebirth at $T.");
    set_property("spell type",({}));
    set_property("must be present", 1);
    set_property("target type", "living");
    set_property("prereq", "summon demon");
    return;
}

void info() {
message("help",
"This spell uses the soul of a demon to return a dead comrad to life.  This spell requres a demon. The spell syntax is: cast *<pow> demonic rebirth at <demon> with <target>",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag)
{
  object person;
//  string name;
  if(!at->id("demon") || at->id("greater demon") || at->id("lesser demon"))
{
    message("info", "You must cast this spell at a demon.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!at->query_owner() || (string)at->query_owner() !=
(string)caster->query_name()) {
    message("info", "The demon must have been summoned and contolled by
you.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "%^RED%^%^BOLD%^Instead of using the demon as a vessel to return "+at->query_true_name()+" to life, the demon attacks you!", caster);
    message("info", (string)at->query_cap_name() + " angrily attacks "+
          (string)caster->query_cap_name() + "!", environment(caster),
          ({ caster, at }));
    at->set_owner("asskicker");
    at->kill_ob(caster, 0);
    remove();
    return;
  }
  if((int)at->query_power() < power) {
    message("info", "The demon must be equal or greater power than the spell.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  if(!args){
     message("info","You must supply a target for this spell.\n", caster);
     caster->add_mp(props["mp cost"]);
     remove();
     return;
  }
  person=find_player(lower_case(args));
  if(!present(person,environment(caster))) {
     message("info","There is noone named "+person->query_name()+" here.\n", caster);
     caster->add_mp(props["mp cost"]);
     remove();
     return;
  }
  if(!person->query_ghost()){
    message("info", "The demon looks at you stupified", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!objectp(person->query("corpse ob"))) {
      person->set("corpse ob", at);
  }
  if(objectp(person->query("corpse ob"))) {
      at->remove();  
  }
  person->revive();
  return;
}
