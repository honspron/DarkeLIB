inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","major puissance");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",77);
    set_property("dev cost", 61);
    set_property("fast dev cost", 180);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You begin to imbue the weapon with magical power.");
    set_property("target message","");
    set_property("observer message","$C begins to enchant a weapon.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell adds a good deal of extra damage to a weapon.  The enchantment "
"limit for this spell is higher than that of minor puissance.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
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
  if((int)at->query_property("enchantment") >= 20) {
    message("info", "This weapon may receive no further major "+
      "enchantments.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  set_work_message("%^CYAN%^You enchant the weapon.");
  start_work(at, caster, 70, power);
  return;
}

void finish_work(object caster, object at, int power) {
  int ench, i, idx;
  mixed tmp;

  if(power <= 0) {
    message("info", "BUG in Enchanter spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "You are finished enchanting!", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations.",
	  environment(caster), ({ caster }) );
	ench = (int)at->query_property("enchantment");
	if(!ench) ench = 0;
	if(ench + power*2 >= 20) {
	  message("info", "This weapon is now enchanted as much as is possible with "+
	      "this spell.", caster);
	  at->set_property("enchantment", 20);
	  ench = 20-(power*2);
	} 
	else
	  {
	    at->set_property("enchantment", ench + power*2);
	  }
  caster->add_exp2(800*power);
	tmp = (mixed)at->query_property("extra long");
  if(!tmp) tmp = ({});
  else if(stringp(tmp)) tmp = ({ tmp });
  idx = -1;
  i = sizeof(tmp);
  while(i--) {
    if(pointerp(tmp[i]) && sizeof(tmp[i]) == 2 &&
      arrange_string(tmp[i][0], 10) == "Puissance:") idx = i;
  }
  if(idx >= 0) tmp = exclude_array(tmp, idx);
  tmp += ({ ({ sprintf("Puissance: %^CYAN%^+%+d", power*2+ench),
    "detect magic" }) });
  at->set_property("extra long", tmp);
  remove();
  return;
}

