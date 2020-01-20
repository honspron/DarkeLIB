inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","nether sight");
    set_property("skill","necromancy");
    set_property("casting time",9);
    set_property("base mp cost",24);
    set_property("dev cost", 20);
    set_property("fast dev cost", 55);
    set_property("spell level", 4);
    set_property("moon","warzau");
    set_property("caster message","You cast dark vision at $T.");
    set_property("target message","$C casts dark vision at you.");
    set_property("observer message","$C casts dark vision at $T.");
    set_property("must be present", 1);
    set_property("target type", "living");
    set_property("duration", 180);
    return;
}

void info() {
message("help",
"This spell allows the target to see in the dark, up to a point.  This is also "
"capable of seeing in a darkness spell of equal or less power.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
  if(flag) {
    message("info", "ACK!  You accidentally blind "+
        (string)at->query_cap_name() + "!", caster);
    message("info", (string)caster->query_cap_name() +
        " accidentally BLINDS you!", at);
    ob = new("/std/spells/shadows/blind_shadow");
    ob->start_shadow(at);
    call_out("expire_blind", props["duration"], at, ob);
    return;
  }
  ob = new("/std/spells/shadows/dvision_shadow");
  ob->set_max(8);
  ob->start_shadow(at, props["duration"], "%^CYAN%^A dark vision spell expires.");
  remove();
  return;
}

void expire_blind(object at, object shad) {
  if(at)
    message("info", "%^CYAN%^The blinding effects of the spell wear off.",
        at);
  if(shad)
    shad->external_destruct(shad);
  return;
}

