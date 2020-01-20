#include <clock.h>

inherit "/std/check_brittle";
inherit "/std/spells/long_term_spell";

string spell_name;
int spell_pow;
string keyword;
string element;
int spell_lev;

void create() {
    ::create();
    set_property("name","lock enchantment");
    set_property("skill","enchantment");
    set_property("duration", "permanent");
    set_property("casting time",4);
    set_property("base mp cost",36);
    set_property("dev cost", 36);
    set_property("fast dev cost", 190);
    set_property("spell level", 7);
    set_property("moon","luna");
    set_property("caster message","You begin to imbue the item with magical power.");
    set_property("target message","");
    set_property("observer message","$C begins to enchant an item.");
    set_property("spell type",({ }));
    set_property("target type", "any");
    set_property("must be present", 1);
    set_property("prereq", "prepare spell");
    return;
}

void info() {
message("help",
"This spell allows you to 'lock' a temporary enchantment on an item, be it a weapon, armour, or "
"whatever.  It does not make the enchantment permamnent, it only allows the bearer of the item to periodically "
"invoke the spell at not mp cost.  How often this can be done depends on the power of the "
"casting.  Upon casting, the spell you wish to lock, and a keyword for invocation must be supplied.  "
"The bearer fo the item invokes the enchantment with 'activate <keyword> on <item>'.  "
"The player may list all enchantments on an item with 'help <item>'.  Note that you CAN ONLY "
"lock spells which are cast at the OBJECT DIRECTLY.  For instance, you may NOT lock demon sword, since it is cast at "
"the demon, not at the sword.  You CAN lock vampiric blade, since it is cast at the sword.  In order to lock a spell, "
"you must either possess the spell yourself or prepare it using 'prepare spell.'  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.  If you are continuing the spell, no arguements need to "
"be supplied.\n\n"
"Syntax: cast *3 lock enchantment at <item> with <spell> keyword:<keyword>\n"
"Ex: cast *3 lock enchantment at long sword with vampiric blade keyword:vampire\n"
"You would activate the above with 'activate vampire on long sword'",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int idx, time, mod;
  string verb, spell, file;
  
  if(!present(at, caster)) {
    message("info", "You must hold the object upon which you wish to cast the spell.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!mapp(at->query_enchantments())) {
    message("info", "That item may not receive locked enchantments.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(flag) {
    message("info", "You misdirect the summoning energies and shatter "+
	    "the item!", caster);
    message("info", (string)caster->query_cap_name() +
	    " inadvertently shatters the item.",
	    environment(caster), ({ caster }) );
    at->remove();
    remove();
    return;
  }
  if(query_in_progress(at, caster)) {
    verb = (string)at->query_property("lock verb:"+
          (string)caster->query_name());
    spell_name = (string)at->query_property("lock spell:"+
          (string)caster->query_name());
    spell_pow = (int)at->query_property("lock pow:"+
          (string)caster->query_name());
    element = (string)at->query_property("lock ele:"+
          (string)caster->query_name());
    message("info", "Using the spell: "+spell_name+", and the "+
        "keyword: "+verb+".", caster);
  } else {
    if(!args || sscanf(args, "%s keyword:%s", spell, verb) != 2) {
      message("info", "See 'help spell lock enchantment' for syntax.",
         caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    while(strlen(verb) > 1 && verb[0] == ' ')
      verb = replace_string(verb, " ", "", 1);
    while((idx=strlen(verb)-1) > 1 && verb[idx] == ' ')
      verb = verb[0..idx-1];
    element = 0;
    spell_pow = 0;
    spell_name = lower_case(spell);
    spell_pow = (int)caster->query_spell_level(spell_name);
    if((string)caster->query("borrowed spell") == spell_name &&
      (int)caster->query("b spell lev") > spell_pow) {
      spell_pow = (int)caster->query("b spell lev");
      element = (string)caster->query("b spell element");
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
    at->set_property("lock verb:"+
          (string)caster->query_name(), verb);
    at->set_property("lock spell:"+
          (string)caster->query_name(), spell_name);
    at->set_property("lock pow:"+
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
  if(!element && file->query_property("elemental spell")) {
    element = at->query_element();
    if(!element) {
      message("info", "You have to use an elemental lore skill to lock "+
          "an elemental spell.", caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
  }
  at->set_property("lock ele:"+
       (string)caster->query_name(), element);
  keyword = verb;
  if(member_array(keyword, keys((mapping)at->query_enchantments())) >= 0) {
    message("info", "That item already has an enchantment with the keyword: "+
      keyword+".", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  set_work_message("%^CYAN%^You enchant the item.");
  spell_lev = idx;
  time = idx*(300+50*power);
  mod = 30+2*props["spell level"];
  start_work(at, caster, (time*mod)/caster->query_skill("enchantment"), power);
  return;
}

void finish_work(object caster, object at, int power) {
//  int ench;

  if(power <= 0) {
    message("info", "BUG in Enchanter spell....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "You are finished enchanting.  Type 'help <item>' to list the enchantments.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations.",
	  environment(caster), ({ caster }) );
  if(!check_brittle(at, caster, power)) {
    remove();
    return;
  }
	at->add_enchantment(keyword, spell_name, spell_pow,
	  2*HOUR/power, element);
	at->set_float_value((float)at->query_float_value() +
	  to_float(spell_lev * spell_lev * 1500));
	at->set_value(to_int((float)at->query_float_value()) +
	  spell_lev * spell_lev * 1500);
  remove();
  return;
}

