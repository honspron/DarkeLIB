inherit "/std/spells/long_term_spell";
inherit "/std/check_brittle";

void create() {
    ::create();
    set_property("name","minor accuracy");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",35);
    set_property("dev cost", 21);
    set_property("fast dev cost", 60);
    set_property("spell level", 4);
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
"This spell makes it a bit easier to hit with a weapon.  There is a limit to "
"how many castings of this spell which a weapon may receive.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int time,mod;
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
  if((int)at->prop("hit bonus") >= 20) {
    message("info", "This weapon may receive no further minor "+
      "accuracy enchantments.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  set_work_message("%^CYAN%^You enchant the weapon.");
   time = 500 + 440*power;
  if (caster->query_skill("enchantment") < 30)
    {
    mod = 1;
    }
  else
    {
    mod = caster->query_skill("enchantment")/30;
    }
  start_work(at, caster, time/mod, power);
  return;
}

void finish_work(object caster, object at, int power) {
  int ench, i, idx;
  int brit = power / 2 + power%2;
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
  if(!check_brittle(at, caster, brit)) {
    remove();
    return;
  }
  ench = (int)at->prop("hit bonus");
  if(!ench) ench = 0;
  if(ench + power*2 >= 20) {
    message("info", "This weapon is now enchanted as much as is possible with "+
	    "this spell.", caster);
    at->set_property("hit bonus", 20);
    ench = 20-(power*2);
  } 
  else
    {
      at->set_property("hit bonus", ench + power*2);
    }
  tmp = (mixed)at->query_property("extra long");
  if(!tmp) tmp = ({});
  else if(stringp(tmp)) tmp = ({ tmp });
  idx = -1;
  i = sizeof(tmp);
  while(i--) {
    if(pointerp(tmp[i]) && sizeof(tmp[i]) == 2 &&
       arrange_string(tmp[i][0], 9) == "Accuracy:") idx = i;
  }
  if(idx >= 0) tmp = exclude_array(tmp, idx);
  tmp += ({ ({ sprintf("Accuracy: %%^CYAN%%^%+d%%", power*2+ench),
		 "detect magic" }) });
  at->set_property("extra long", tmp);
  caster->add_exp2(400*power);
  remove();
  return;
}

