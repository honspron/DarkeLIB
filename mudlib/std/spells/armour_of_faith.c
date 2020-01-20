inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","armour of faith");
    set_property("skill","prayer");
    set_property("casting time",5);
    set_property("base mp cost", 51);
    set_property("dev cost", 21);
    set_property("fast dev cost", 52);
    set_property("spell level", 4);
    set_property("moon", "ankh");
    set_property("caster message",
		 "You cast armour of faith at $T.");
    set_property("target message","$C casts armour of faith upon you.");
    set_property("observer message",
		 "$C casts armour of faith at $T.");
    set_property("spell type",({ "protection" }));
    set_property("target type", "living");
    set_property("protection types", ([
         "crushing" : 6, "impaling" : 6, "cutting" : 6, "impact" : 7,
        "strike":6, "stress":4, "constriction":5 ]) );
    set_property("duration", 360);
    set_property("prereq", "holy armour");
    set_property("stack key", "holy armour");
    set_property("stack num", 6);
    set_property("must be present", 1);
    return;
}

void info() {
message("help", @TEXT
This prayer protects the recipient against PHYSICAL attacks.
The protection is relatively mild, but the spell can be stacked.

This prayer is functionally similiar to Holy Armour excepting that
the protection is against the physical not magical.  Holy Armour and
Armour of Faith each count in the spell stacking.
TEXT
, this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {

  if((int)at->query("holy armour #") >= 6) {
    message("info", (string)at->query_cap_name() +
	    " cannot receive any more armour of faith spells.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  at->set("holy armour #", (int)at->query("holy armour #") + 1);
  delayed_call("remove_stack", props["duration"], at);
  ::spell_func(caster, at, power, args, flag);
  return;
}

void remove_stack(object at) {
  if(!objectp(at)) return;
  at->set("holy armour #", (int)at->query("holy armour #") - 1);
  remove();
  return;
}
