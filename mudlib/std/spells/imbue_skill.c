inherit "/std/spells/long_term_spell";

string skill_name;
int skill_pow;
int skill_lev;

void create() {
    ::create();
    set_property("name","imbue skill");
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
"This skill allows you to imbue an enchanter's ring (available at most magic shops) with "
"a certain skill.  The wearer of the ring may then use the skill as if he/she had trained it.  "
"You must either possess the skill you wish to imbue or borrow it with 'prepare skill'.  "
"This is a long-term spell (see help long-term), and it takes very much real "
"time to cast.  If you are interrupted while casting, "
"you may pick up again at a later time.  If you are continuing the skill, no arguements need to "
"be supplied.  If the ring already has that skill imbued on it, it will be replaced by the new "
"casting, even if it is lower.  You can view the skills and skills locked on a ring with 'help <ring>'.\n\n"
"Syntax: cast *3 imbue skill at <item> with <skill>\n"
"Ex: cast *3 imbue skill at ring 1 with skin corpse\n"
"NOTE: The skill will be imbued at a leval equal to 1/6th the level of the imbued skill times the power of the "
"spell.\n"
"ALSO: If you are continuing the skill, no arguements need be supplied.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  int idx, time, mod;
  string file;
  
  if(!present(at, caster)) {
    message("info", "You must hold the object upon which you wish to cast the skill.",
	    caster);
	  caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!at->id("enchanter ring")) {
    message("info", "You must cast this skill on an enchanter ring.",
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
  if(query_in_progress(at, caster)) {
    skill_name = (string)at->query_property("imbue skill:"+
          (string)caster->query_name());
    skill_pow = (int)at->query_property("imbue sk pow:"+
          (string)caster->query_name());
    message("info", "Using the skill: "+skill_name+".", caster);
  } else {
    if(!args) {
      message("info", "See 'help skill imbue skill' for syntax.",
         caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    while(strlen(args) > 1 && args[0] == ' ')
      args = replace_string(args, " ", "", 1);
    while((idx=strlen(args)-1) > 1 && args[idx] == ' ')
      args = args[0..idx-1];
    skill_pow = 0;
    skill_name = lower_case(args);
    skill_pow = (int)caster->query_skill(skill_name);
    if((string)caster->query("borrowed skill") == skill_name &&
      (int)caster->query("b skill lev") > skill_pow) {
      skill_pow = (int)caster->query("b skill lev");
      caster->set("borrowed skill", 0);
      caster->set("b skill lev", 0);
      message("info", "You use your prepared skill.",
        caster);
    }
    if(!skill_pow) {
      message("info", "You must have the skill: "+skill_name+" or "+
          "borrow it using 'prepare skill'.", caster);
      caster->add_mp(props["mp cost"]);
      remove();
      return;
    }
    at->set_property("imbue skill:"+
          (string)caster->query_name(), skill_name);
    at->set_property("imbue sk pow:"+
          (string)caster->query_name(), skill_pow);
  }
  seteuid(getuid());
  file = "/std/skills/"+replace_string(skill_name, " ", "_");
  if(!file_exists(file+".c")) {
    message("info", "Cannot find the skill file...this is a BUG.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  idx = (int)file->query_dev();
  set_work_message("%^CYAN%^You enchant the ring.");
  skill_lev =  2 * idx/3;
  time = (idx/2)*(600 + 450*power);
  mod = 40+2*props["spell level"];
  start_work(at, caster, (2*time*mod)/caster->query_skill("enchantment"), power);
  return;
}

void finish_work(object caster, object at, int power) {
//  int ench;

  if(power <= 0) {
    message("info", "BUG in Enchanter skill....unable to complete.",
	    environment(caster));
    remove();
    return;
  }
  message("info", "You are finished enchanting.  Type 'help <ring>' to list the skills/skills.", caster);
  message("info", (string)caster->query_cap_name() + " utters some "+
	  "magical incantations.",
	  environment(caster), ({ caster }) );
        skill_pow = skill_pow * power / 6;
	at->set_skill(skill_name, skill_pow);
//         at->set_float_value((float)at->query_float_value() +
//           to_float(skill_lev * skill_lev * 2500));
//         at->set_value(to_int((float)at->query_float_value()) +
//           skill_lev * skill_lev * 2500);
        caster->add_exp2(skill_lev * 1000 * power);
  remove();
  return;
}

