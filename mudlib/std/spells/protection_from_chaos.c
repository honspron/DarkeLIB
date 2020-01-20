inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","protection from chaos");
    set_property("skill","prayer");
    set_property("casting time",9);
    set_property("base mp cost",25);
    set_property("dev cost", 8);
    set_property("fast dev cost", 20);
    set_property("spell level", 3);
    set_property("moon", "ankh");
    set_property("caster message",
		 "You cast protection from chaos at $T.");
    set_property("target message","$C casts protection from chaos upon you.");
    set_property("observer message",
		 "$C casts protection from chaos at $T.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([ "disruption" : 8 ]));
    set_property("duration", 180);
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell imbues the recipient from chaos and disruption-based attacks, "
"such as those from chaotic lords, vacid elementals, etc.",
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
