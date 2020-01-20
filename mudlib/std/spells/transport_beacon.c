inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","transport beacon");
    set_property("skill","enchantment");
    set_property("casting time",24);
    set_property("base mp cost",41);
    set_property("dev cost", 71);
    set_property("fast dev cost", 210);
    set_property("spell level", 14);
    set_property("moon","luna");
    set_property("caster message","You summon a transport beacon.");
    set_property("target message","");
    set_property("observer message","$C utters some magical incantations.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    set_property("duration", "until quit");
    return;
}

void info() {
message("help",
"This spell is for use with the 'transport rune' spell.  When "
"you cast a transport rune, you MUST have a transport beacon SOMEWHERE "
"on the mud.  The transport rune will then cause it's victims to be "
"transported to that location.  If the becon moves or disappears, the "
"rune will still transport to the location of the beacon at the time of casting.  "
"There is no way to reconfigure a transport rune to transport to a different "
"location once cast.  Once cast, any transport runes cast must be at a power "
"level equal or lesser than the power of the transport beacon.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  
  if(flag) {
    message("info", "Despite the fumble, you seem okay.", caster);
    caster->set("transport beacon",
      ([ "room" : "/d/standard/square", "power" : 6 ]) );
    remove();
    return;
  }
  if(environment(caster)->query_property("no teleport")) {
     message("info", "You may not create a transport beacon here.",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  caster->set("transport beacon",
      ([ "room" : base_name(environment(caster)),
        "power" : power ]) );
  message("info", "Your transport runes will be directed to this location.", caster);
  remove();
  return;
}
