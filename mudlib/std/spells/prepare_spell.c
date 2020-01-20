inherit "/std/spells/spell";

object me;
string skill;
string lender;
int spell_pow;

void create() {
    ::create();
    set_property("name","prepare spell");
    set_property("skill","enchantment");
    set_property("casting time",9);
    set_property("base mp cost",41);
    set_property("dev cost", 37);
    set_property("fast dev cost", 99);
    set_property("spell level", 7);
    set_property("moon","luna");
    set_property("caster message","You cast prepare spell at $T.");
    set_property("target message","$C casts prepare spell at you.");
    set_property("observer message","$C casts prepare spell at $T.");
    set_property("spell type",({ }));
    set_property("target type", "player");
    set_property("must be present", 1);
    set_property("duration", "until quit");
    return;
}

void info() {
message("help",
"This spell is necessary to use in conjunction with the "
"'imbue spell' and 'lock enchantment' spells if you wish to imbue a spell which you "
"do not have.  It allows you to 'borrow' a spell from a player (players only) "
"for the sole purpose of casting imbue spell.  The borrowed spell will be at a level "
"equal to the power level at which prepare spell is cast, or the spell level of "
"the player from which the spell is borrowed, whichever is lower.  Once the spell is cast "
"on a player, he/she must type 'allow <caster>' (<caster> is you) in 60 seconds or "
"the spell will fail.\n"
"Syntax: cast *3 prepare spell at <player> with <spell>\n"
"NOTE: You can only borrow one spell at a time.  The last one borrowed "
"will take precedence.  This spell may only be cast on a player your level "
"or lower.",
this_player());
}

void spell_func(object caster, object at, int power, string args, int flag) {
  object ob;
  if(!args) {
    message("info", "See 'help spell prepare spell' for syntax.",
        caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  me = caster;
  skill = lower_case(args);
  if(flag) {
    message("info", "The spell merely fails.", caster);
    remove();
    return;
  }
  if(!at->query_spell_level(skill)) {
    message("info", "That palyer does not have the skill: '"+skill+
          ".", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(!at->spell_exists(skill)) {
    message("info", "You cannot borrow a spell that a player received "+
      "through magic items or other bonuses, only through training.",
      caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if((int)at->query_level() > (int)caster->query_level()) {
    message("info", "That player is higher level than you.", caster);
    caster->add_mp(props["mp cost"]);
    remove();
    return;
  }
  seteuid(getuid());
  ob = present("borrow soul", at);
  if(ob) ob->remove();
  ob = new("/wizards/diewarzau/obj/misc/borrow_soul");
  ob->set_allow(caster, this_object());
  ob->move(at);
  message("info", "You have 60 seconds to type 'allow "+
    (string)caster->query_name()+"' to lend your "+
    skill+" spell.", at);
  spell_pow = power;
  lender = (string)at->query_cap_name();
  call_out("expire_time", 60);
  return;
}

void expire_time() {
  if(!me) {
    remove();
    return;
  }
  message("info", lender+" has not responded.  Your spell fails.",
    me);
  remove();
  return;
}

void allowed(object who) {
  int spell_lev;
  string file;
  
  if(!me) return;
  spell_lev = (int)who->query_base_spell(skill);
  if(spell_lev > spell_pow) spell_lev = spell_pow;
  file = "/std/spells/"+replace_string(skill, " ", "_");
  if(!file_exists(file+".c")) {
    message("info", "Cannot find the spell file...this is a BUG.",
        me);
    me->add_mp(props["mp cost"]);
    remove();
    return;
  }
  if(file->query_property("elemental spell")) {
    if(!who->query_element()) {
      message("info", "When you borrow an elemental spell, the lender MUST "+
          "use an elemental lore skill to specify the element.  The spell fails.",
        me);
      me->add_mp(props["mp cost"]);
      remove();
      return;
    }
    else
      me->set("b spell element", (string)who->query_element());
  }
  message("info", "spell: "+skill+" prepared at level "+
    spell_lev+"%.", me);
  me->set("borrowed spell", skill);
  me->set("b spell lev", spell_lev);
  return;
}

