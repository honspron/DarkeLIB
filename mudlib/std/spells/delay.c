#define NO_STORE ({ "store spell", "delay", "link" })

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","delay");
    set_property("skill","sorcery");
    set_property("casting time",6);
    set_property("base mp cost",5);
    set_property("dev cost", 70);
    set_property("fast dev cost", 185);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast delay.");
    set_property("target message","");
    set_property("observer message","$C casts delay.");
    set_property("spell type",({ }));
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This spell allows you to set another spell on a delay timer...a 'spell "
"grenade', if you will.  The usage is:\n"
"     cast *<pow> delay at <spell (with args)> delay <time>\n"
"     example: cast *4 delay at fireball at dragon delay time 60\n"
"          ^This will delay the casting of a fireball for 60 rounds (2 minutes).\n\n"
"The magic points for the spell are spent at the time of casting.\n"
"NOTE: You may not delay a spell for less than its casting time.\n"
"ALSO: You MAY cast spells while waiting for the delayed spell to go "
"off.  You may only have one spell per full 7 levels of the caster set up "
"on a delay.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  string spell, sp_name, new_arg;
  int time;
  object sp_ob;

  if(flag) {
    message("info", "You accidentally drain some of your mp.",
          caster);
    caster->add_mp(-30*power);
    remove();
    return;
  }
  if(sizeof(explode(args, " ")) && explode(args, " ")[0] == "delay") {
    message("info", "You may not delay a delay spell.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(sscanf(args, "%s delay time %d", spell, time) != 2) {
    message("info", "Incorrect syntax...see 'help spell delay' for help.",
          caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(member_array(spell, NO_STORE) >= 0) {
    message("info", "You may not delay that spell.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if((int)caster->query("delayed spells") >= ((int)caster->query_level() / 7)) {
    message("info", "You already have the maximum number of allowed spells on "
            "a delay.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(sscanf(spell, "%s at %s", sp_name, new_arg) != 2) {
    sp_name = spell;
    new_arg = 0;
  }
  sp_name = lower_case(sp_name);
  if(power > (int)caster->query_spell_level(sp_name)) {
    message("info", "You do not know the spell '"+sp_name+"' at the power level "+power+".",
            caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(time < 60)
  seteuid(getuid());
  sp_ob = new("/std/spells/"+replace_string(sp_name, " ", "_"));
  if(time < (int)sp_ob->query_property("casting time")) {
    message("info", "You may not delay a spell for less than its original "
          "casting time.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  sp_ob->set_property("casting time", time);
  sp_ob->begin_casting(caster, new_arg, power);
  caster->set_casting(0);
  caster->set_magic_round(0);
  message("info", "The spell will go off in "+time+" rounds.\n", caster);
  if(!caster->query("delayed spells")) caster->set("delayed spells", 0);
  caster->set("delayed spells", 1 + (int)caster->query("delayed spells"));
  call_out("dec_delay_amount", time*2, caster);
  return;
}

void dec_delay_amount(object caster) {
  if(!caster) {
    remove();
    return;
  }
  if(!caster->query("delayed spells")) caster->set("delayed spells", 0);
  caster->set("delayed spells", -1 + (int)caster->query("delayed spells"));
  remove();
  return;
}

