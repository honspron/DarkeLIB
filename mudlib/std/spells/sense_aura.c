inherit "/std/spells/spell";



void create() {

    ::create();

    set_property("name","sense aura");

    set_property("skill","enchantment");

    set_property("casting time",5);

    set_property("base mp cost",20);

    set_property("dev cost", 13);

    set_property("fast dev cost", 45);

    set_property("spell level", 3);

    set_property("moon","luna");

    set_property("caster message","You cast sense aura at $T.");

    set_property("target message","");

    set_property("observer message","$C casts sense aura at $T.");

    set_property("spell type",({ }));

    set_property("target type", "any");

    set_property("duration", "instantaneous");

    return;

}



void info() {

message("help",

"This spell is used to sense the strength of the magical aura on "

"enchanted weapons.  The greater the aura, the greater the chance "

"that a weapon will shatter if it is enchanted further.  At power "

"levels 1-3, an estimate of the strength of the aura is provided, "

"with accuracy increasing with power level.  At levels 4-6, additionally, "

"an estimate of the chance that a weapon will break upon its next enchantment "

"is provided as well.",

this_player());

}



void spell_func(object caster, object at, int power, string args, int flag) {

  int old;

  string tmp;



  if(!at->is_weapon()) {

    message("info", "This spell must be cast at a weapon.",

	    caster);

    caster->add_mp(props["mp cost"]);

    return;

  }

  if(flag) {

    message("info", "You receive no information from the spell.",

	    caster);

    old = (int)at->prop("brittle");

    old += 2+random(4);

    at->set_property("brittle", old);

    remove();

    return;

  }

  old = (int)at->prop("brittle");

  old += (random(30) - 15) / power;

  if(old < 0) old = 0;

  tmp = "%^CYAN%^The weapon's aura is ";

  switch(old) {

  default:

  case 0..3:

    tmp += "undetectable";

    break;

  case 4..10:

    tmp += "very weak";

    break;

  case 11..19:

    tmp += "weak";

    break;

  case 20..25:

    tmp += "not very strong";

    break;

  case 26..35:

    tmp += "fairly strong";

    break;

  case 36..55:

    tmp += "very strong";

    break;

  case 56..200:

    tmp += "blazing";

    break;

  }

  tmp += "\n";

  if(power >= 4) {

    tmp += "Upon further enchantment, the weapon has ";

    switch(old) {

    default:

    case 0..29:

      tmp += "no chance";

      break;

    case 30..35:

      tmp += "a small chance";

      break;

    case 36..50:

      tmp += "a modest chance";

      break;

    case 51..75:

      tmp += "a good chance";

      break;

    case 76..200:

      tmp += "almost a 100% chance";

      break;

    }

    tmp += " of breaking.\n";

  }

  message("info", "You divine the following from the weapon...\n"+

	  tmp, caster);

  remove();

  return;

}









