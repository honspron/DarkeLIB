inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","scry");
    set_property("skill","magery");
    set_property("casting time",8);
    set_property("base mp cost",35);
    set_property("dev cost",52);
    set_property("fast dev cost",140);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast scry.");
    set_property("target message","");
    set_property("observer message","$C concentrates intently.");
    set_property("no target", 1);
    set_property("save mod", "intelligence");
    set_property("duration", 240);
    set_property("prereq", "clairvoyance");
    return;
}

void info() {
message("help",
"This spell allows you to obtain a fix on a distant target.  "
"It is necessary to set up distant spells, such as transport, "
"summon, or call lightning...any spell that requires a scry first.\n"
"Syntax: cast *1 scry at <who>",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int lev, diff;
  object who;

  if(!args) {
    message("info", "Who do you wish to scry?", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  args = lower_case(args);
  at = find_player(args);
  if(!at) at = find_living(args);

  who = at;
  if(!who) {
    message("info", "Cannot find: '"+args+"' on the mud.", caster);
    message("info", (string)caster->query_cap_name()+"'s spell fails.",
        environment(caster), ({ caster }));
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(environment(who) && environment(who)->query_property("no scry")) {
    message("info", "You feel as though your scry is blocked by a mystic force.", caster);
    remove();
    return;
  }
  if(environment(caster) && environment(caster)->query_property("no scry")) {
    message("info", "You feel as though your scry is blocked by a mystic force.", caster);
    remove();
    return;
  }
  lev = (int)who->query_level();
  diff = 5 + (int)caster->query_level() - lev;
  if (random(16) > (diff + power))
  {
      message("info", "Your scry is resisted!", caster);
      message("info", "You resist " + (string)caster->query_true_name() + 
	      "'s scry!", at);
      remove();
      return;
  }

  if(who->query("scryguard")) {
    if(random(100) < (int)who->query("scryguard")/power) {
      message("info", "You fail to break "+(string)who->query_cap_name() +
          "'s scryguard.", caster);
      message("info", "Your scryguard blocks "+
            (string)caster->query_cap_name()+"'s scry attempt.",
            who);
      remove();
      return;
    }
    else {
      message("info", (string)who->query_cap_name() + " has a scryguard, "+
            "but you break through it.", caster);
      message("info", "You scryguard was insufficient to block "+
            (string)caster->query_cap_name()+"'s scry.", who);
    }
  }
  caster->set("scry", who);
  caster->set("scry time", time() + props["duration"]);
  message("info", "You have successfully fixed "+
      (string)who->query_cap_name() + "'s location.  The "+
      "scry will be effective for "+props["duration"]/60+
      " minutes or until you cast a distance spell which requires "+
      "the scry.", caster);
  remove();
  return;
}

