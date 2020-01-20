#define VALID_PACKS ({ "hit points", "magic points", "armour", \
  "damage spells", "healing spells", "protection spells", "melee damage" })

inherit "/std/spells/long_term_spell";

string package;

void create() {
    ::create();
    set_property("name","improve statue");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",32);
    set_property("dev cost", 7);
    set_property("fast dev cost", 18);
    set_property("spell level", 1);
    set_property("moon","luna");
    set_property("caster message","You begin to improve the statue.");
    set_property("target message","");
    set_property("observer message","$C begins to magically mold a statue.");
    set_property("spell type",({ }));
    set_property("target type", "living");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell allows you to customize your statue.  Each statue may receive 2 customization "
"'packages', and you have 7 to choose from:\n"
"hit points               Extra hp\n"
"magic points             Extra mp\n"
"melee damage             Souped up damage in combat\n"
"damage spells            an assortment of attack spells\n"
"healing spells           spells to heal the statue\n"
"protection spells        an array of self-rpotection spells\n"
"armour                   better AC\n"
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you wish to continue casting, you only need to supply the "
"target, no additional arguements.  If you are interrupted while casting, "
"you may pick up again at a later time.  The power of the spell increases the power of the "
"package.\n"
"Syntax: cast *3 improve statue at <statue> with <package>\n"
"Ex: cast *3 imporve statue at statue 2 with damage spells\n"
"Ex (if continuing): cast *2 improve statue at statue 3",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int time, mod;
//  string mat;
//  object ob, *ob_p;
  
  if(!at->id("statue") || !at->is_pet() ||
    (string)at->query_owner() != (string)caster->query_name()) {
    message("info", "You must cast this spell at a statue owned by you.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the statue!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the statue.",
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
      message("info", "That statue has already received that package.",
        caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    if(pointerp(at->query_property("imp packages")) &&
      sizeof((string *)at->query_property("imp packages")) >= 2) {
      message("info", "That statue has already has 2 packages on it.",
        caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    at->set_property("current improve", package);
  }
  set_work_message("%^CYAN%^You improve the statue.");
  time = 600+100*power;
  mod = 30+2*props["spell level"];
  start_work(at, caster, (time*mod)/caster->query_skill("enchantment"), power);
  return;
}

void finish_work(object caster, object at, int power) {
  //object ob;

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
    message("info", "That statue has already received that package.  The spell fails.",
      caster);
    remove();
    return;
  }
  if(pointerp(at->query_property("imp packages")) &&
    sizeof((string *)at->query_property("imp packages")) >= 2) {
    message("info", "That statue has already has 2 packages on it. The spell fails.",
      caster);
    remove();
    return;
  }
  at->improve_me(package, power);
  message("info", "Statue has received the package: "+package, caster);
  remove();
  return;
}

