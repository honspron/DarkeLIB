#include <std.h>

inherit "/std/spells/long_term_spell";
inherit "/std/check_brittle";

void create() {
    ::create();
    set_property("name","true weapon");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",77);
    set_property("dev cost", 91);
    set_property("fast dev cost", 278);
    set_property("spell level", 17);
    set_property("moon","luna");
    set_property("caster message","You begin to imbue the weapon with magical power.");
    set_property("target message","");
    set_property("observer message","$C begins to enchant a weapon.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("prereq", "major puissance");
    return;
}

void info() {
message("help",
"This is a truly powerful weapon enchantment and any weapon may only receive one of these.  "
"It increases the intensity of any critical hit done by the weapon.  Due to the extreme power of this "
"spell, it is effective only up to power level 4, not 6.  Casting the spell at power levels 5 or 6 will "
"have the same effect as 3 and 4, respectively, but will take half the time to cast.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int mult, time, mod;
  
  if(!at->is_weapon()) {
    message("info", "You must cast this spell at a weapon.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the weapon!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the weapon.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  if((int)at->query_property("true weapon") ||
    (intp(at->query_enh_critical()) &&
    (int)at->query_enh_critical() > 2))  {
    message("info", "This weapon already has true weapon or a similar spell cast on it.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(power > 4) mult = 2;
  else mult = 1;
  set_work_message("%^CYAN%^You enchant the weapon.");
  time = 3600 + 800 *((power>4)?(power-2):power)/mult;
  mod = 40+2*props["spell level"];
  start_work(at, caster, (time*mod)/caster->query_skill("enchantment"), power);
  return;
}

void finish_work(object caster, object at, int power) {
  mixed ench;
  string *types;
  int i;
//  mapping tmp;
  mixed val;

  if(power <= 0) {
    message("info", "BUG in Enchanter spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  caster->add_exp2(10000*power);
  message("info", "You are finished enchanting!", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations.",
	  environment(caster), ({ caster }) );
  if(power > 4) power -= 2;
  if(!check_brittle(at, caster, power*4)) {
    remove();
    return;
  }
  ench = (mixed)at->query_enh_critical();
  if(!ench) ench = 0;
  if(mapp(ench)) {
    types = DAMAGE_TYPES;
    i = sizeof(types);
    while(i--) {
      if(ench[types[i]])
	ench[types[i]] += power;
      else ench[types[i]] = power;
    }
    at->set_enh_critical(ench);
  }
  else
    at->set_enh_critical(ench+power);
  at->set_property("true weapon", 1);
  val = (mixed)at->query_property("extra long");
  if(!val) val = ({});
  else if(stringp(val)) val = ({ val });
  val += ({ ({ "This weapon has %^BLUE%^%^BOLD%^True Weapon%^RESET%^." ,
		 "detect magic" }) });
  at->set_property("extra long", val);
  remove();
  return;
}

