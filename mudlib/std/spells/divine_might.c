inherit "/std/spells/spell";


void create() {

    ::create();

    set_property("name","divine might");
    set_property("skill","body alteration");
    set_property("casting time",6);
    set_property("base mp cost",15);
    set_property("dev cost", 7);
    set_property("fast dev cost", 17);
    set_property("spell level", 2);
    set_property("moon","luna");
    set_property("caster message","You cast divine might on $T.");
    set_property("target message","$C casts divine might on you.");
    set_property("observer message","$C casts divine might on $T.");
    set_property("spell type",({ "stat mod" }));
    set_property("stat dice", "1D6");
    set_property("stats", ({ "strength" }) );
    set_property("target type", "living");
    set_property("must be present",1);
    set_property("duration", 480);
    set_property("stack key", "divine might");
    set_property("stack num", 2);
    return;
}

void info() {
message("help",
"This spell gives the recipient a temporary increase in strength.",
this_player());
}
void spell_func(object caster, object at, int power, string args, int flag) {

  if((int)at->query("divine might #") >= 3) {
    message("info", (string)at->query_cap_name() +
            " cannot receive any more divine might spells.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->set("divine might #", (int)at->query("divine might #") + 1);
  call_out("remove_stack", props["duration"], at);
  ::spell_func(caster, at, power, args, flag);
  return;
}

void remove_stack(object at) {
  if(!objectp(at)) return;
  at->set("divine might #", (int)at->query("divine might #") - 1);
  message("info", "%^CYAN%^A divine might spell expires.", at);
  remove();
  return;
}
