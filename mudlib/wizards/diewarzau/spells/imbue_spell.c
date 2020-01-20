inherit "/std/spells/long_term_spell";

string spell_name;
int spell_pow;
int spell_lev;

void create() {
    ::create();
    set_property("name","imbue spell");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",36);
    set_property("dev cost", 89);
    set_property("fast dev cost", 270);
    set_property("spell level", 17);
    set_property("moon","luna");
    set_property("caster message","You begin to imbue the ring with magical power.");
    set_property("target message","");
    set_property("observer message","$C begins to enchant a ring.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    return;
}

void info() {
message("help",
"This spell allows you to imbue an enchanter's ring (available at most magic shops) with "
"a certain spell.  The wearer of the ring may then cast the spell as if he/she had trained it.  "
"You must either possess the spell you wish to imbue or borrow it with 'prepare spell'.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.  If you are continuing the spell, no arguements need to "
"be supplied.  If the ring already has that spell imbued on it, it will be replaced by the new "
"casting, even if it is lower.  You can view the skills and spells locked on a ring with 'help <ring>'.\n\n"
"Syntax: cast *3 imbue spell at <item> with <spell>\n"
"Ex: cast *3 imbue spell at ring 1 with fireball\n"
"NOTE: The spell will be imbued at a power equal to either the power of the imbue spell or the power of the "
"spell itself, whichever is lower.\n"
"ALSO: If you are continuing the spell, no arguements need be supplied.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int idx;
  string file;
  
  if(!present(at, caster)) {
    message("info", "You must hold the object upon which you wish to cast the spell.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!at->id("enchanter ring")) {
    message("info", "You must cast this spell on an enchanter ring.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the ring!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the ring.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  if(at->query_active()) {
    message("info", "That ring already has a skill or spell on it.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(query_in_progress(at, caster)) {
    spell_name = (string)at->query_property("imbue spell:"+
          (string)caster->query_name());
    spell_pow = (int)at->query_property("imbue pow:"+
          (string)caster->query_name());
    message("info", "Using the spell: "+spell_name+".", caster);
  } else {
    if(!args) {
      message("info", "See 'help spell imbue spell' for syntax.",
         caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    while(strlen(args) > 1 && args[0] == ' ')
      args = replace_string(args, " ", "", 1);
    while((idx=strlen(args)-1) > 1 && args[idx] == ' ')
      args = args[0..idx-1];
    spell_pow = 0;
    spell_name = lower_case(args);
    spell_pow = (int)caster->query_spell_level(spell_name);
    if((string)caster->query("borrowed spell") == spell_name &&
      (int)caster->query("b spell lev") > spell_pow) {
      spell_pow = (int)caster->query("b spell lev");
      caster->set("borrowed spell", 0);
      caster->set("b spell lev", 0);
      message("info", "You use your prepared spell.",
        caster);
    }
    if(!spell_pow) {
      message("info", "You must have the spell: "+spell_name+" or "+
          "borrow it using 'prepare spell'.", caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    at->set_property("imbue spell:"+
          (string)caster->query_name(), spell_name);
    at->set_property("imbue pow:"+
          (string)caster->query_name(), spell_pow);
  }
  seteuid(getuid());
  file = "/std/spells/"+replace_string(spell_name, " ", "_");
  if(!file_exists(file+".c")) {
    message("info", "Cannot find the spell file...this is a BUG.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  idx = (int)file->query_property("spell level");
  set_work_message("%^CYAN%^You enchant the ring.");
  spell_lev = idx;
  start_work(at, caster, 120, power);
  return;
}

void finish_work(object caster, object at, int power) {
  int ench;

  if(power <= 0) {
    message("info", "BUG in Enchanter spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "You are finished enchanting.  Type 'help <ring>' to list the skills/spells.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations.",
	  environment(caster), ({ caster }) );
	if(power < spell_pow) spell_pow = power;
	at->set_spell_level(spell_name, spell_pow);
	at->set_float_value((float)at->query_float_value() +
	  to_float(spell_lev * spell_lev * 2500));
	at->set_value(to_int((float)at->query_float_value()) +
	  spell_lev * spell_lev * 2500);
  remove();
  return;
}

