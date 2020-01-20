inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","freeze skin");
    set_property("skill","necromancy");
    set_property("casting time",4);
    set_property("base mp cost", 32);
    set_property("dev cost", 37);
    set_property("fast dev cost", 82);
    set_property("spell level", 6);
    set_property("moon", "ankh");
    set_property("caster message",
		 "You cast freeze skin at $T.");
    set_property("target message","$C casts freeze skin upon you.");
    set_property("observer message",
		 "$C casts freeze skin at $T.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([
        "cold":15
    ]) );
    set_property("duration", 240);
    set_property("stack key", "freeze skin");
    set_property("stack num", 2);
    set_property("must be present", 1);
    return;
}

void info() {
message("help", @TEXT
This spell makes the skin of the recipient so cold that
cold attacks have very little effect on him/her.  This
spell can be stacked twice.
TEXT
, this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  if((int)at->query("holy armour #") >= 2) {
    message("info", (string)at->query_cap_name() +
	    " cannot receive any more freeze skin spells.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->set("freeze skin #", (int)at->query("freeze skin #") + 1);
  call_out("remove_stack", props["duration"], at);
  ::spell_func(caster, at, power, args, flag);
  return;
}

void remove_stack(object at) {
  if(!objectp(at)) return;
  at->set("freeze skin #", (int)at->query("freeze skin #") - 1);
  remove();
  return;
}
