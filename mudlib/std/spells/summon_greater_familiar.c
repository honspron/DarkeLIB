inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","summon greater familiar");
    set_property("skill","magery");
    set_property("casting time",110);
    set_property("base mp cost", 350);
    set_property("dev cost", 84);
    set_property("fast dev cost", 245);
    set_property("spell level",15);
    set_property("moon","luna");
    set_property("caster message","You summon a greater familiar.");
    set_property("target message","");
    set_property("observer message","$C summons a greater familiar.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", 600);
    set_property("prereq", "summon familiar");
    return;
}

void info() {
message("help",
"This spell summons a creature to serve the caster, binding the soul "
"of the creature to the caster.  The creature may aid the caster in "
"combat.  Greater power summons more powerful familiars.  You may also "
"borrow magic points from the familiar.  Once the familiar is summoned, "
"typing 'help familiar' will tell you how.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;

  seteuid(getuid());
ob = new("/std/diewarzau/obj/pet/greater_familiar");
  ob->set_up(power);
  ob->move(environment(caster));
  ob->set_dur(props["duration"]);
  ob->set_owner((string)caster->query_name());
  message("info", "You summon "+lower_case((string)ob->query_short()) +
          ".", caster);
  message("info", "A "+lower_case((string)ob->query_short()) +
          " appears.", environment(caster), ({ caster }));
  if(flag) {
    message("info", "You are unable to bond the creature to your soul, " +
            "and it attacks you!", caster);
    ob->kill_ob(caster, 0);
  }
  else
    ob->set_master((string)caster->query_name());
  remove();
  return;
}
