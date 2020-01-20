inherit "/std/spells/long_term_spell";

void create() {
    ::create();
    set_property("name","minor fortification");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",43);
    set_property("dev cost", 17);
    set_property("fast dev cost", 56);
    set_property("spell level", 3);
    set_property("moon","luna");
    set_property("caster message","You begin to imbue the armour with magical power.");
    set_property("target message","");
    set_property("observer message","$C begins to enchant a piece of armour.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell adds a small bit of extra protection to a piece of armour.  There is a "
"limit to which any piece of armour can be enchanted, and you will be informed when that limit is reached.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int time, mod;
  if(!at->is_armour()) {
    message("info", "You must cast this spell at a piece of armour.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the armour!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the armour.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  if((int)at->query_property("enchantment") >= 10) {
    message("info", "This armour may receive no further minor "+
      "enchantments.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  set_work_message("%^CYAN%^You enchant the armour.");
  time = 660+210*power;
  mod = 30+2*props["spell level"];
  start_work(at, caster, (time*mod)/caster->query_skill("enchantment"), power);
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
	if(ench + power >= 10) {
	  message("info", "This armour is now enchanted as much as is possible with "+
	      "this spell.", caster);
	  at->set_property("enchantment", 10);
	  ench = 10-power;
	} 
	else
	  {
	    at->set_property("enchantment", ench + power);
	  }
  caster->add_exp2(300*power);
	tmp = (mixed)at->query_property("extra long");
  if(!tmp) tmp = ({});
  else if(stringp(tmp)) tmp = ({ tmp });
  idx = -1;
  i = sizeof(tmp);
  while(i--) {
    if(pointerp(tmp[i]) && sizeof(tmp[i]) == 2 &&
      arrange_string(tmp[i][0], 14) == "Fortification:") idx = i;
  }
  if(idx >= 0) tmp = exclude_array(tmp, idx);
  tmp += ({ ({ sprintf("Fortification: %%^CYAN%%^%+d", power+ench),
    "detect magic" }) });
  at->set_property("extra long", tmp);
  remove();
  return;
}

