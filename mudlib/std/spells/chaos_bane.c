inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","chaos bane");
    set_property("skill","prayer");
    set_property("casting time",19);
    set_property("base mp cost",76);
    set_property("dev cost", 108);
    set_property("fast dev cost", 235);
    set_property("spell level", 18);
    set_property("moon", "ankh");
    set_property("caster message",
		 "You cast chaos bane at $T.");
    set_property("target message","$C casts chaos bane upon you.");
    set_property("observer message",
		 "$C casts chaos bane at $T.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([ "disruption" : 35 ]));
    set_property("duration", 180);
    set_property("must be present", 1);
    set_property("prereq", "protection from chaos");
    return;
}

void info() {
message("help",
"This spell is the ultimate protection from chaos and disruption-based "
"attacks, such as those from chaotic lords, vacid elementals, etc.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  if((int)at->query("chaos prot #") >= 3) {
    message("info", (string)at->query_cap_name() +
	    " cannot receive any more protection spells.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->set("chaos prot #", (int)at->query("chaos prot #") + 1);
  call_out("remove_stack", props["duration"], at);
  ::spell_func(caster, at, power, args, flag);
  return;
}

void remove_stack(object at) {
  if(!objectp(at)) return;
  at->set("chaos prot #", (int)at->query("chaos prot #") - 1);
  remove();
  return;
}
