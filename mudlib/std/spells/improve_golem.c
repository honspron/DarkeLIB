#define VALID_PACKS ({ "hit points", "magic points", "armour", \
  "damage spells", "healing spells", "protection spells", "melee damage" })

inherit "/std/spells/long_term_spell";

string package;

void create() {
    ::create();
    set_property("name","improve golem");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",32);
    set_property("dev cost", 56);
    set_property("fast dev cost", 170);
    set_property("spell level", 11);
    set_property("moon","luna");
    set_property("caster message","You begin to improve the golem.");
    set_property("target message","");
    set_property("observer message","$C begins to magically mold a golem.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("prereq", "improve statue");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell allows you to customize your golem.  Each golem may receive 2 customization "
"'packages', and you have 7 to choose from:\n"
"hit points               Extra hp\n"
"magic points             Extra mp\n"
"melee damage             Souped up damage in combat\n"
"damage spells            an assortment of attack spells\n"
"healing spells           spells to heal the golem\n"
"protection spells        an array of self-rpotection spells\n"
"armour                   better AC\n"
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you wish to continue casting, you only need to supply the "
"target, no additional arguements.  If you are interrupted while casting, "
"you may pick up again at a later time.  The power of the spell increases the power of the "
"package.\n"
"Syntax: cast *3 improve golem at <golem> with <package>\n"
"Ex: cast *3 imporve golem at golem 2 with damage spells\n"
"Ex (if continuing): cast *2 improve golem at golem 3",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
 // int ingots;
 // string mat;
 // object ob, *ob_p;
  
  if(!at->id("golem") || !at->is_pet() ||
    (string)at->query_owner() != (string)caster->query_name()) {
    message("info", "You must cast this spell at a golem owned by you.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the golem!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the golem.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  if(query_in_progress(at, caster)) {
    package = (string)at->query_property("current improve");
    message("info", "Continuing spell, using package: "+package,
      caster);
  }
  else {
    if(!stringp(args) || member_array(lower_case(args),
        VALID_PACKS) < 0) {
      message("info", "You must supply one of the "+
        "available improvement packages as an arguement.",
        caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    package = lower_case(args);
    if(pointerp(at->query_property("imp packages")) &&
      member_array(package, (string *)at->query_property("imp packages")) >= 0) {
      message("info", "That golem has already received that package.",
        caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    if(pointerp(at->query_property("imp packages")) &&
      sizeof((string *)at->query_property("imp packages")) >= 2) {
      message("info", "That golem has already has 2 packages on it.",
        caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    at->set_property("current improve", package);
  }
  set_work_message("%^CYAN%^You improve the golem.");
  start_work(at, caster, 1200 + 300 * power, power);
  return;
}

void finish_work(object caster, object at, int power) {
//  object ob;

  if(power <= 0) {
    message("info", "BUG in Enchanter spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "You are finished casting.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations.",
	  environment(caster), ({ caster }) );
  seteuid(getuid());
  at->remove_property("current improve");
  if(pointerp(at->query_property("imp packages")) &&
    member_array(package, (string *)at->query_property("imp packages")) >= 0) {
    message("info", "That golem has already received that package.  The spell fails.",
      caster);
    remove();
    return;
  }
  if(pointerp(at->query_property("imp packages")) &&
    sizeof((string *)at->query_property("imp packages")) >= 2) {
    message("info", "That golem has already has 2 packages on it. The spell fails.",
      caster);
    remove();
    return;
  }
  at->improve_me(package, power);
  message("info", "Golem has received the package: "+package, caster);
  remove();
  return;
}

