#define NO_STORE ({ "store spell", "delay", "link" })

inherit "/std/spells/spell";

void create() {
    ::create();
    set_property("name","store spell");
    set_property("skill","sorcery");
    set_property("casting time",1);
    set_property("base mp cost",0);
    set_property("dev cost", 69);
    set_property("fast dev cost", 205);
    set_property("spell level", 12);
    set_property("moon","luna");
    set_property("caster message","You cast store spell.");
    set_property("target message","");
    set_property("observer message","$C casts store spell.");
    set_property("spell type",({ }));
    set_property("prereq", "delay");
    set_property("no target", 1);
    return;
}

void info() {
message("help",
"This spell may be used to store a spell which may later be cast for "
"no cost.  It's casting cost is equal to the casting cost of the spell "
"to be stored plus 30*power level.  Store spell must be cast at a power "
"level equal to the power of spell you wish to store.\n"
"\n"
"Syntax (storing the spell):\n"
"  cast *4 store spell at prepare fireball\n"
"  (stores a level 4 fireball)\n"
"\nSyntax (casting the stored spell):\n"
"  cast *4 store spell at beggar\n"
"  (casts the stored spell at a beggar)\n",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  string spell;
  object sp_ob;
  mapping tmp;
  int cost;
  
  if(flag) {
    message("info", "Fortunately, you seem unharmed by the fumble.",
            caster);
    message("info", (string)caster->query_cap_name() +
          " looks none the worse for wear, however.", caster);
    caster->set("stored spell", 0);
    remove();
    return;
  }
  if(sscanf(args, "prepare %s", spell)) {
    spell = lower_case(spell);
    if((int)caster->query_spell_level(spell) < power) {
      message("info", "You do not know the spell '"+spell+"' at "+
          "power level "+power+".", caster);
      remove();
      return;
    }
    if(member_array(spell, NO_STORE) >= 0) {
      message("info", "You may not store that spell.", caster);
      remove();
      return;
    }
    cost = 30*power;
    seteuid(getuid());
    sp_ob = new("/std/spells/"+replace_string(spell, " ", "_"));
    cost += power * (int)sp_ob->query_property("base mp cost");
    if(cost > (int)caster->query_mp()) {
      message("info", "You do not have enough mp to store that spell at "+
            "that power level.", caster);
      remove();
      return;
    }
    call_out("store_spell", (int)sp_ob->query_property("casting time"),
      caster, spell, power);
    message("info", "%^CYAN%^You begin preparing to store a "+spell+" spell.",
          caster);
    caster->add_mp(-1*cost);
    return;
  }
  tmp = (mapping)caster->query("stored spell");
  if(!tmp || !mapp(tmp)) {
    message("info", "You do not have a spell stored!", caster);
    remove();
    return;
  }
  power = tmp["power"];
  spell = lower_case(tmp["spell"]);
  sp_ob = new("/std/spells/"+replace_string(spell, " ", "_"));
  sp_ob->set_property("casting time", 1);
  sp_ob->set_property("base mp cost", 0);
  sp_ob->begin_casting(caster, args, power);
  remove();
  return;
}

void store_spell(object caster, string spell, int power) {
  caster->set("stored spell", ([ "spell" : spell, "power" : power ]));
  message("info", "You have stored a "+spell+" spell.  It will stay until "+
        "you cast it, quit, or prepare another spell.", caster);
  remove();
  return;
}
