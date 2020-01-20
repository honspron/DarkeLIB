inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","blur");
    set_property("skill","illusionism");
    set_property("casting time",5);
    set_property("base mp cost",37);
    set_property("dev cost", 32);
    set_property("fast dev cost", 87);
    set_property("spell level", 7);
    set_property("moon","luna");
    set_property("caster message","You cast blur at $T.");
    set_property("target message","$C casts blur at you.");
    set_property("observer message","$C casts blur at $T.");
    set_property("spell type",({ }));
    set_property("duration", 40);
    set_property("stack key", "blur");
    set_property("stack num", 3);
    set_property("target type", "living");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell causes the target to blur slightly and blend in with the "
"surroundings.  This will make him/her substantially harder to hit in "
"combat.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag)
    message("info", "Oddly enough, "+(string)at->query_cap_name() +
        " seems much easier to see...", caster);
  if(at->query_blurred() && !flag) {
    message("info", "You may only cast 1 blur spell on a target.",
       caster);
    message("info", "%^CYAN%^"+(string)caster->query_cap_name() +
          "'s spell fails.", environment(caster), ({ caster }) );
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!flag)
    message("info", (string)at->query_cap_name() +
        " seems to fade slightly into the surroundings.",
        environment(caster), ({ caster }) );
  ob = new("/std/spells/shadows/blur_shadow");
  ob->set_penalty((flag?-1:1) * power * (3 + random(6) + random(6)));
  ob->start_shadow(at, props["duration"], "%^CYAN%^A blur spell wears off.");
  remove();
  return;
}
